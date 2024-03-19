#ifndef ROCKET_NET_TCP_TCP_SERVER_H__
#define ROCKET_NET_TCP_TCP_SERVER_H__

#include<set>
#include"tcp_acceptor.h"
#include"tcp_connection.h"
#include"net_addr.h"
#include"../../net/eventLoop.h"
#include "../../net/io_thread_group.h"
namespace rocket{
class TcpServer{
public:
    TcpServer(NetAddr::ptr local_addr);

    ~TcpServer();

    void start();
private:
    void init();

    void onAccept();
private:
    TcpAcceptor::ptr m_acceptor;
    NetAddr::ptr m_local_addr;  //本地监听地址

    EventLoop* m_main_event_loop{NULL}; //mainReactor

    IOThreadGroup* m_io_thread_group{NULL};//subReactor组

    FdEvent* m_listen_fd_event{NULL};
    int m_client_counts{0};


    std::set<TcpConnection::ptr>m_client;
};

}

#endif