#ifndef ROCKET_NET_TCP_TCP_CLIENT_H__
#define ROCKET_NET_TCP_TCP_CLIENT_H__
#include<memory>
#include "net_addr.h"
#include "../eventLoop.h"
#include "tcp_connection.h"
#include "../coder/abstract_protocol.h"
#include"../../common/error_code.h"
#include"../timer_event.h"
namespace rocket{
class TcpClient{
public:
    typedef std::shared_ptr<TcpClient> ptr;
    TcpClient(NetAddr::ptr peer_addr);

    ~TcpClient();

    //异步connect
    //如果connect完成，done会被执行
    void connect(std::function<void()>done);

    //异步地发送Message
    //如果发送request成功，会调用done函数，函数的入参就是message对象
    void writeMessage(AbstractProtocol::ptr message,std::function<void(AbstractProtocol::ptr)>done);

    //异步地读取Message
    //如果发送request成功，会调用done函数，函数的入参就是message对象
    void readMessage(const std::string& req_id,std::function<void(AbstractProtocol::ptr)>done);

    void stop();

    int getConnectErrorCode();

    std::string getConnectErrorInfo();

    NetAddr::ptr getPeerAddr() const{return m_peer_addr;}
    NetAddr::ptr getLocalAddr() const {return m_local_addr;}

    void initLocalAddr();


    void addTimerEvent(TimerEvent::ptr timer_event);

private:
    NetAddr::ptr m_peer_addr;
    NetAddr::ptr m_local_addr;
    EventLoop* m_event_loop{NULL};

    int m_fd{-1};
    FdEvent* m_fd_event{NULL};
    TcpConnection::ptr m_connection;

    int m_connect_errcode{0};
    std::string m_connect_error_info;
};


}

#endif