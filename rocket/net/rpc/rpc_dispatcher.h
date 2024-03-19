

#ifndef ROCKET_NET_RPC_RPC_DISPATCHER_H__
#define ROCKET_NET_RPC_RPC_DISPATCHER_H__

#include"../coder/abstract_protocol.h"
#include"../coder/tinypb_protocol.h"

#include<google/protobuf/service.h>
#include<google/protobuf/descriptor.h>
#include<google/protobuf/message.h>
namespace rocket{

class TcpConnection;

class RpcDispatcher{
public:

    static RpcDispatcher* GetRpcDispatcher();
    typedef std::shared_ptr<google::protobuf::Service> service_ptr;
    void dispatch(AbstractProtocol::ptr resquest,AbstractProtocol::ptr response,TcpConnection* connection);

    void registerService(service_ptr service);

    void setTinyPBError(std::shared_ptr<TinyPBProtocol>msg,int32_t err_code,const std::string err_info);
private:
    //从全名中解析服务名和方法名
    bool parseServiceFullName(const std::string& full_name,std::string& service_name,std::string& method_name);
private:
    //存放已注册的service对象
    std::map<std::string,service_ptr>m_service_map;
};


}

#endif