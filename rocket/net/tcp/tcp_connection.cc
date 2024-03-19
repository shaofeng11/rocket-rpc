#include<unistd.h>

#include"tcp_connection.h"
#include "../../common/log.h"

namespace rocket{
TcpConnection::TcpConnection(rocket::EventLoop* eventLoop,int fd,int buffer_size,rocket::NetAddr::ptr peer_addr,rocket::NetAddr::ptr local_addr,TcpConnectionType type):
                                m_eventLoop(eventLoop)
                                ,m_local_addr(local_addr)
                                ,m_peer_addr(peer_addr)
                                ,m_state(NotConnected)
                                ,m_fd(fd)
                                ,m_connectionType(type){
    m_in_buffer=std::make_shared<TcpBuffer>(buffer_size);
    m_out_buffer=std::make_shared<TcpBuffer>(buffer_size);

    m_fd_event=FdEventGroup::GetFdEventGroup()->getFdEvent(fd);
    m_fd_event->setNonBlock();
    //给m_fd_event添加读事件，绑定到onRead回调中
    if(m_connectionType==TcpConnectionByServer){
        listenRead();
    }
    //如果连接类型是客户端的话，就给他一个编码器，将数据发送给Server
    m_coder=new TinyPBCoder();
}

TcpConnection::~TcpConnection(){
    if(m_coder){
        delete m_coder;
        m_coder=NULL;
        LOG_DEBUG("~TcpConnection"); 
    }
    
}



//读取客户端发来的数据
void TcpConnection::onRead(){
    LOG_DEBUG("on read");
    if(m_state!=Connected){
        LOG_ERROR("onRead error,client has already disconnected,addr[%s],clientfd[%d]",
                m_peer_addr->toString().c_str(),m_fd);
        return;
    }
    bool is_read_all=false;
    bool is_close=false;
    while(!is_read_all){
        if(m_in_buffer->writeAble()==0){
            m_in_buffer->resizeBuffer(2*m_in_buffer->m_buffer.size());
        }

        int read_count=m_in_buffer->writeAble();
        int write_index=m_in_buffer->getWriteIndex();
        int rt=read(m_fd,&(m_in_buffer->m_buffer[write_index]),read_count);
        LOG_DEBUG("success read %d bytes from addr[%s],client fd[%d]"
                    ,rt,m_peer_addr->toString().c_str(),m_fd);
        if(rt>0){
            m_in_buffer->moveWriteIndex(rt);
            if(rt==read_count){
                continue;
            }else if(rt<read_count){
                is_read_all=true;
                break;
            }
        //rt<=0,说明对端关闭了
        }else if(rt==0){
            is_close=true;
            break;
        }else if(rt==-1 && errno==EAGAIN){
            is_read_all=true;
            break;
        }
    }

    //对端连接关闭了
    if(is_close){
        LOG_INFO("peer closed,peer addr[%s],clientfd [%d]",m_peer_addr->toString().c_str(),m_fd);
        clear();
        return;
    }
    if(!is_read_all){
        LOG_ERROR("not read all data");
    }

    //TODO:简单的echo，后面补充RPC协议解析
    excute();
}

void TcpConnection::excute(){
    LOG_DEBUG("excute");
    if(m_connectionType==TcpConnectionByServer){
            // 将 RPC 请求执行业务逻辑，获取 RPC 响应, 再把 RPC 响应发送回去
        // std::vector<char>tmp;
        // int size=m_in_buffer->readAble();
        // tmp.resize(size);
        // m_in_buffer->readFromBuffer(tmp,size);
        std::vector<AbstractProtocol::ptr>result;
        std::vector<AbstractProtocol::ptr>replay_messages;
        m_coder->decode(result,m_in_buffer);
        for(size_t i=0;i<result.size();++i){
            //1.针对每一个请求，调用rpc方法。获取响应message
            //2.将响应message放入到缓冲区，监听可写事件回包
            LOG_INFO("success get request[%s] from client[%s]",result[i]->m_msgId.c_str(),m_peer_addr->toString().c_str());
            std::shared_ptr<TinyPBProtocol>message=std::make_shared<TinyPBProtocol>();
            // message->m_pb_data="hello,this is rocket rpc test data";
            // message->m_msgId=result[i]->m_msgId;
            RpcDispatcher::GetRpcDispatcher()->dispatch(result[i],message,this);
            replay_messages.emplace_back(message);
        }
        m_coder->encode(replay_messages,m_out_buffer);
        //添加写事件，绑定onWrite回调函数
        listenWrite();
    }else{
        //从buffer中decode得到message对象，执行回调
        std::vector<AbstractProtocol::ptr>result;
        m_coder->decode(result,m_in_buffer);

        for(size_t i=0;i<result.size();++i){
            std::string req_id=result[i]->m_msgId;
            auto it=m_read_dones.find(req_id);
            if(it!=m_read_dones.end()){
               it->second(result[i]);
               m_read_dones.erase(it);
            }
            
        }
    }
}

void TcpConnection::onWrite(){
    LOG_DEBUG("on write");
    if(m_state!=Connected){
        LOG_ERROR("onWrite error,client has already disconnected,addr[%s],clientfd[%d]",
                m_peer_addr->toString().c_str(),m_fd);
        return;
    }

    if(m_connectionType==TcpConnectionByClient){
        //1.将message encode得到字节流
        //将数据写入到buffer.然后全部发送
        std::vector<AbstractProtocol::ptr>messages;
        for(size_t i=0;i<m_write_dones.size();++i){
            messages.push_back(m_write_dones[i].first);
        }
        m_coder->encode(messages,m_out_buffer);
    }
    bool is_write_all=false;
    while(true){
        if(m_out_buffer->readAble()==0){
            LOG_DEBUG("no data need to send to client [%s]",m_peer_addr->toString().c_str());
            is_write_all=true;
            break;
        }
        int write_size=m_out_buffer->readAble();
        int read_index=m_out_buffer->getReadIndex();
        int rt=write(m_fd,&(m_out_buffer->m_buffer[read_index]),write_size);

        if(rt>=write_size){
            is_write_all=true;
            LOG_DEBUG("send over,no data need to send to client [%s]",m_peer_addr->toString().c_str());
            break;
        }
        if(rt==-1&&errno==EAGAIN){
            //发送缓冲区满了，不能再发送了
            //等下次fd可写的时候再次发送数据即可
            LOG_ERROR("write data error,errno=EAGAIN adn rt==-1");
            break;
        }
    }
    if(is_write_all){
        m_fd_event->cancel(FdEvent::OUT_EVENT);
        m_eventLoop->addEpollEvent(m_fd_event);
    }

    if(m_connectionType==TcpConnectionByClient){
        LOG_DEBUG(" xie hui diao hanshu ");
        for(size_t i=0;i<m_write_dones.size();++i){
            m_write_dones[i].second(m_write_dones[i].first);
        }
        m_write_dones.clear();   
    }
    
}

void TcpConnection::clear(){
    //处理一些关闭连接后的清理动作
    if(m_state==Close){
        return;
    }

    m_fd_event->cancel(FdEvent::IN_EVENT);
    m_fd_event->cancel(FdEvent::OUT_EVENT);

    m_eventLoop->delEpollEvent(m_fd_event);

    m_state=Close;
}

void TcpConnection::shutdown(){
    if(m_state==Close||m_state==NotConnected){
        return;
    }
    m_state=HalfClosing;

    //关闭读写，服务器不会再对这个fd进行读写操作了
    //发送FIN报文，触发了四次挥手的第一个阶段
    //当fd发生可读事件，但可读数据为0，表示对端发生了FIN报文
    ::shutdown(m_fd,SHUT_RDWR);
}

void TcpConnection::listenWrite(){
    m_fd_event->listen(FdEvent::OUT_EVENT,std::bind(&TcpConnection::onWrite,this));

    m_eventLoop->addEpollEvent(m_fd_event);
}

void TcpConnection::listenRead(){
    m_fd_event->listen(FdEvent::IN_EVENT,std::bind(&TcpConnection::onRead,this));

    m_eventLoop->addEpollEvent(m_fd_event);
}

void TcpConnection::pushSendMessage(AbstractProtocol::ptr message,std::function<void(AbstractProtocol::ptr)> done){
    m_write_dones.push_back(std::make_pair(message,done));
}

void TcpConnection::pushReadMessage(const std::string& req_id,std::function<void(AbstractProtocol::ptr)> done){
    m_read_dones.insert(std::make_pair(req_id,done));
}
}