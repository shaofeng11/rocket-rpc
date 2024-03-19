#ifndef ROCKET_NET_TCP_TCP_ACCEPTOR_H
#define ROCKET_NET_TCP_TCP_ACCEPTOR_H
#include<memory>
#include "net_addr.h"
namespace rocket{
class TcpAcceptor{
public:
    typedef std::shared_ptr<TcpAcceptor>ptr;
    TcpAcceptor(NetAddr::ptr local_addr);
    ~TcpAcceptor();

    std::pair<int,NetAddr::ptr> accept();

    int getListenFd() const{return m_listenfd;}
private:
    //
    NetAddr::ptr m_local_addr;
    int m_listenfd{-1};

    int m_family{-1};
};

}

#endif