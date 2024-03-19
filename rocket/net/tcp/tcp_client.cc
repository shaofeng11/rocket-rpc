#include<unistd.h>
#include "tcp_client.h"
#include "../../common/log.h"
namespace rocket{

TcpClient::TcpClient(NetAddr::ptr peer_addr)
                    :m_peer_addr(peer_addr){
    //一个线程只有一个eventloop，获取当前线程的eventloop
    m_event_loop=EventLoop::getCurrentEventLoop();
    m_fd=socket(peer_addr->getFamily(),SOCK_STREAM,0);
    if(m_fd<0){
        LOG_ERROR("TcpClient::TcpClient() error,fails to create fd");
        return;
    }
    m_fd_event=FdEventGroup::GetFdEventGroup()->getFdEvent(m_fd);

    m_fd_event->setNonBlock();
    m_connection=std::make_shared<TcpConnection>(m_event_loop,m_fd,128,peer_addr,nullptr,TcpConnectionByClient);
    m_connection->setConnectionType(TcpConnectionByClient);
}

TcpClient::~TcpClient(){
    if(m_fd>0){
        close(m_fd);
    }
}

void TcpClient::connect(std::function<void()>done){
    int rt=::connect(m_fd,m_peer_addr->getSockAddr(),m_peer_addr->getSockLen());
    if(rt==0){
        initLocalAddr();
        LOG_DEBUG("connect [%s] success",m_peer_addr->toString().c_str()); 
        m_connection->setState(Connected);
        if(done){
            done();
        }
    }else if(rt==-1){
        if(errno==EINPROGRESS){
            //epoll监听可写事件，判断错误码
            m_fd_event->listen(FdEvent::OUT_EVENT,[this,done](){
                int rt=::connect(m_fd,m_peer_addr->getSockAddr(),m_peer_addr->getSockLen());
                if((rt<0&&errno==EISCONN)||(rt==0)){
                    LOG_DEBUG("connect [%s] success",m_peer_addr->toString().c_str()); 
                    initLocalAddr();
                    m_connection->setState(Connected);
                }else{
                    if(errno==ECONNREFUSED){
                        m_connect_errcode=ERROR_PEER_CLOSED;
                        m_connect_error_info="connect refused,sys error="+std::string(strerror(errno));
                    }else{
                        m_connect_errcode=ERROR_FAILED_CONNECT;
                        m_connect_error_info="connect error,sys error="+std::string(strerror(errno));
                    }
                   LOG_ERROR("connect error,errno=%d,error=%s",errno,strerror(errno));
                    close(m_fd);
                    m_fd=socket(m_peer_addr->getFamily(),SOCK_STREAM,0);
                }
                //需要去掉可写事件的监听，不然会一直触发
                m_event_loop->delEpollEvent(m_fd_event);
                //如果连接成功才会执行回调函数
                if(done){
                    done();
                }
            });
            m_event_loop->addEpollEvent(m_fd_event);
            if(!m_event_loop->isLooping()){
                m_event_loop->loop();
            }
        }
       else{
        LOG_ERROR("connec error,errno=%d,error=%s",errno,strerror(errno));
        m_connect_errcode=ERROR_FAILED_CONNECT;
        m_connect_error_info="connect error,sys error = "+std::string(strerror(errno));
        if(done){
            done();
        }
       } 
    }
}

void TcpClient::stop(){
    if(m_event_loop->isLooping()){
        m_event_loop->stop();
    }
}

void TcpClient::writeMessage(AbstractProtocol::ptr message,std::function<void(AbstractProtocol::ptr)>done){
    //1.把message对象写到Connection的buffer，done也写入
    //2.启动connection可写事件
    m_connection->pushSendMessage(message,done);
    m_connection->listenWrite();
}

//异步地读取Message
//如果发送request成功，会调用done函数，函数的入参就是message对象
void TcpClient::readMessage(const std::string& req_id,std::function<void(AbstractProtocol::ptr)>done){
    //1.监听可读事件
    //2.从buffer中decode得到message对象,判断是否req_id 相等，相等则读成功，执行回调
    m_connection->pushReadMessage(req_id,done);
    m_connection->listenRead();
}

int TcpClient::getConnectErrorCode(){
    return m_connect_errcode;
}

std::string TcpClient::getConnectErrorInfo(){
    return m_connect_error_info;
}

void TcpClient::initLocalAddr(){
    sockaddr_in local_addr;
    socklen_t len=sizeof(local_addr);

    int ret=getsockname(m_fd,(sockaddr*)&local_addr,&len);
    if(ret!=0){
        LOG_ERROR("initLocalAddr error,getsockaname error,errno=%d,error=%s",errno,strerror(errno));
    }  
    m_local_addr =std::make_shared<IPNetAddr>(local_addr);
}


void TcpClient::addTimerEvent(TimerEvent::ptr timer_event){
    m_event_loop->addTimerEvent(timer_event);
}


}