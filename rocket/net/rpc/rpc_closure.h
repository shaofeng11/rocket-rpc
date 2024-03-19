#ifndef ROCKET_NET_RPC_RPC_CPNTROLLER_H__
#define ROCKET_NET_RPC_RPC_CPNTROLLER_H__

#include <google/protobuf/stubs/callback.h>
#include<functional>
namespace rocket{

class RpcClosure: public google::protobuf::Closure{
public:
    RpcClosure(std::function<void()>cb):m_cb(cb){}

    void Run() override{
        if(m_cb){
            m_cb();
        }
    }
private:
    std::function<void()>m_cb{NULL};
};

}


#endif