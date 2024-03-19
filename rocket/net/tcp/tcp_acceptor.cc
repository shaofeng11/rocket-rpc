#include<assert.h>
#include<sys/socket.h>
#include<fcntl.h>
#include "../../common/log.h"
#include "tcp_acceptor.h"
#include "net_addr.h"

namespace rocket{
TcpAcceptor::TcpAcceptor(NetAddr::ptr local_addr):m_local_addr(local_addr){
    if(!local_addr->isValid()){
        LOG_ERROR("invalid local addr %s",local_addr->toString().c_str());
        exit(0);
    }
    m_family=m_local_addr->getFamily();

    m_listenfd=socket(m_family,SOCK_STREAM,0);
    if(m_listenfd<0){
        LOG_ERROR("invalid listenfd %d",m_listenfd);
        exit(0);
    }

    int val=1;
    if(setsockopt(m_listenfd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val))!=0){
        LOG_ERROR("setsockopt REUSEADDR error,errno=%d,error=%s",errno,strerror(errno));
    }

    socklen_t len=m_local_addr->getSockLen();
    if(bind(m_listenfd,m_local_addr->getSockAddr(),len)!=0){
        LOG_ERROR("bind error,errno=%d,error=%s",errno,strerror(errno));
        exit(0);
    }
    if(listen(m_listenfd,1000)!=0){
        LOG_ERROR("listen error,errno=%d,error=%s",errno,strerror(errno));
        exit(0);
    }
}
TcpAcceptor::~TcpAcceptor(){

}


std::pair<int,NetAddr::ptr> TcpAcceptor::accept(){
    if(m_family==AF_INET){
        sockaddr_in client_addr;
        memset(&client_addr,0,sizeof(client_addr));
        socklen_t client_addr_len=sizeof(client_addr);
        //调用系统accept函数
        int rt=::accept(m_listenfd,reinterpret_cast<sockaddr*>(&client_addr),&client_addr_len);
        if(rt<0){
            LOG_ERROR("accept error,errno=%d,error=%s",errno,strerror(errno));
        }
        //peer_addr是服务器地址
        IPNetAddr::ptr peer_addr=std::make_shared<rocket::IPNetAddr>(client_addr);
        LOG_INFO("A client has accepted success,peer addr[%s]",peer_addr->toString().c_str());
        return std::make_pair(rt,peer_addr);
    }
    return std::make_pair(-1,nullptr);    
}
}