#ifndef ROCKET_NET_TCP_TCP_CONNECTION_H
#define ROCKET_NET_TCP_TCP_CONNECTION_H
#include<memory>
#include<queue>
#include "net_addr.h"
#include"tcp_buffer.h"
#include "../io_thread.h"
#include "../fd_event_group.h"
#include"../coder/abstract_protocol.h"
#include "../coder/abstract_coder.h"
#include "../coder/string_coder.h"
#include "../coder/tinypb_coder.h"
#include "../rpc/rpc_dispatcher.h"
namespace rocket{

enum TcpState{
        NotConnected=1,
        Connected=2,
        HalfClosing=3,
        Close=4
};

enum TcpConnectionType{
    TcpConnectionByServer=1,//作为服务端使用，代表跟对端客户端的连接
    TcpConnectionByClient=2,//作为客户端使用，代表跟对端服务端的连接
};
class TcpConnection{
public:
    typedef std::shared_ptr<TcpConnection>ptr;

    TcpConnection(EventLoop* eventLoop,int fd,int buffer_size,rocket::NetAddr::ptr peer_addr,rocket::NetAddr::ptr local_addr,TcpConnectionType type);

    ~TcpConnection();
    void onRead();

    void excute();

    void onWrite();

    void setState(const TcpState state) { m_state=state;}

    TcpState getState() const {return m_state;}

    void clear();

    //服务端主动关闭连接，处理一些不收发数据的连接
    void shutdown();

    void setConnectionType(TcpConnectionType type) { m_connectionType=type;}

    void listenWrite();

    void listenRead();

    void pushSendMessage(AbstractProtocol::ptr message,std::function<void(AbstractProtocol::ptr)> done);

    void pushReadMessage(const std::string& req_id,std::function<void(AbstractProtocol::ptr)> done);

    NetAddr::ptr getLocalAddr() const{ return m_local_addr;}
    NetAddr::ptr getPeerAddr() const{ return m_peer_addr;}

private:
    rocket::EventLoop* m_eventLoop{NULL}; //代表持有该连接的io线程
    rocket::NetAddr::ptr m_local_addr;
    rocket::NetAddr::ptr m_peer_addr;

    rocket::TcpBuffer::ptr m_in_buffer; //接收缓冲区
    rocket::TcpBuffer::ptr m_out_buffer; //发送缓冲区

    

    FdEvent* m_fd_event{NULL};

    TcpState m_state;

    int m_fd{0};

    TcpConnectionType m_connectionType;

    //std::pair<AbstractProtocol::ptr,std::function<void(AbstractProtocol::ptr)>>
    std::vector<std::pair<AbstractProtocol::ptr,std::function<void(AbstractProtocol::ptr)>>>m_write_dones;

    //key为req_id
    std::map<std::string,std::function<void(AbstractProtocol::ptr)>>m_read_dones;

    //std::shared_ptr<RpcDispatcher> m_dispather;

    AbstractCoder* m_coder {NULL};

};
}

#endif