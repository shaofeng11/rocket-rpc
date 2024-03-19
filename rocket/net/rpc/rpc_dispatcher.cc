#include "rpc_dispatcher.h"
#include"../../common/log.h"
#include"../coder/tinypb_protocol.h"
#include"../../common/error_code.h"
#include "rpc_controller.h"
#include"../tcp/net_addr.h"
#include "../tcp/tcp_connection.h"
namespace rocket{

static RpcDispatcher* g_rpc_dispatcher=NULL;

RpcDispatcher* RpcDispatcher::GetRpcDispatcher(){
    if(g_rpc_dispatcher!=NULL){
        return g_rpc_dispatcher;
    }
    g_rpc_dispatcher=new RpcDispatcher;
    return g_rpc_dispatcher;
}


void RpcDispatcher::dispatch(AbstractProtocol::ptr request,AbstractProtocol::ptr response,TcpConnection* connection){
    //请求和响应，父类转化为子类
    std::shared_ptr<TinyPBProtocol>req_protocol=std::dynamic_pointer_cast<TinyPBProtocol>(request);
    std::shared_ptr<TinyPBProtocol>rsp_protocol=std::dynamic_pointer_cast<TinyPBProtocol>(response);

    std::string method_full_name=req_protocol->m_method_name;


    std::string service_name;
    std::string method_name;

    //请求的id 和响应的id一样
    rsp_protocol->m_msgId=request->m_msgId;
    //方法名也一样
    rsp_protocol->m_method_name=req_protocol->m_method_name;

    if(!parseServiceFullName(method_full_name,service_name,method_name)){
        //后面补充出错处理
        setTinyPBError(rsp_protocol,ERROR_PARSE_SERVICE_NAME,"parse service name error");
        return;
    }
    auto it=m_service_map.find(method_name);
    if(it==m_service_map.end()){
        //出错处理
        LOG_ERROR("%s | service name[%s] not found",req_protocol->m_msgId.c_str(),service_name.c_str());
        setTinyPBError(rsp_protocol,ERROR_SERVICE_NOT_FOUND,"service not found");
        return;
    }
    service_ptr service=(*it).second;

    //根据方法名找到该方法文件描述符
   const google::protobuf::MethodDescriptor* method=service->GetDescriptor()->FindMethodByName(method_name);
    if(method==NULL){
        LOG_ERROR("%s |method name[%s] not found in service[%s]",req_protocol->m_msgId.c_str(),method_name.c_str(),service_name.c_str());
        setTinyPBError(rsp_protocol,ERROR_METHOD_NOT_FOUND,"method not found");
        return;
    }

    //找request type,声明一个空的请求对象
    google::protobuf::Message* req_msg= service->GetRequestPrototype(method).New();

    //反序列化，将请求结构体中的 pb_data反序列化为string类型的req_msg
    if(!req_msg->ParseFromString(req_protocol->m_pb_data)){
        LOG_ERROR("%s |deserlize error",req_protocol->m_msgId.c_str());
        setTinyPBError(rsp_protocol,ERROR_FAILED_DESERIALIZE,"deserialize error");
        if(req_msg){
            delete req_msg;
            req_msg=NULL;
        }
        return;
    }
    LOG_INFO("%s |get rpc request[%s]",req_protocol->m_msgId.c_str(),req_msg->ShortDebugString().c_str())

    //找response type,声明一个空的响应对象
    google::protobuf::Message* rsp_msg=service->GetResponsePrototype(method).New();

    RpcController rpcController;

    rpcController.SetLocalAddr(connection->getLocalAddr());
    rpcController.SetPeerAddr(connection->getPeerAddr());
    rpcController.SetmsgId(req_protocol->m_msgId);

    //service就是OrderImpl类型的对象，method是makeorder成员函数，传入req_msg和rsp_msg,根据makeorder函数写入rsp_msg
    service->CallMethod(method,&rpcController,req_msg,rsp_msg,NULL);

    //将rsp_msg的pd_data序列化
    if(rsp_msg->SerializeToString(&rsp_protocol->m_pb_data)){
        LOG_ERROR("%s |serlize error,origin message [%s]",req_protocol->m_msgId.c_str(),rsp_msg->ShortDebugString().c_str());
        setTinyPBError(rsp_protocol,ERROR_FAILED_SERIALIZE,"serialize error");
        if(req_msg){
            delete req_msg;
            req_msg=NULL;
        }
        if(rsp_msg){
            delete rsp_msg;
            rsp_msg=NULL;
        }
        return;
    }
    rsp_protocol->m_err_code=0;
    LOG_INFO("%s | dispatch success,request[%s],response[%s]",req_protocol->m_msgId.c_str(),req_msg->ShortDebugString().c_str(),rsp_msg->ShortDebugString().c_str());
    delete req_msg;
    delete rsp_msg;
    req_msg=NULL;
    rsp_msg=NULL;
}

void RpcDispatcher::registerService(service_ptr service){
    std::string service_name=service->GetDescriptor()->full_name();
    m_service_map[service_name]=service;
}

//从全名中解析服务名和方法名
bool RpcDispatcher::parseServiceFullName(const std::string& full_name,std::string& service_name,std::string& method_name){
    if(full_name.empty()){
        LOG_ERROR("full name empty");

        return false;
    }

    size_t i=full_name.find_first_of(".");
    if(i==full_name.npos){
        LOG_ERROR("not find . in full name[%s]",full_name.c_str());
        return false;
    }
    service_name=full_name.substr(0,i);
    method_name=full_name.substr(i+1,full_name.length()-1-i);
    LOG_INFO("parser service_name[%s],and method_name[%s] from full name[%s]",service_name.c_str(),method_name.c_str(),full_name.c_str())
    return true;
}

void RpcDispatcher::setTinyPBError(std::shared_ptr<TinyPBProtocol>msg,int32_t err_code,const std::string err_info){
    msg->m_err_code=err_code;
    msg->m_err_info=err_info;
    msg->m_err_info_len=err_info.length();
}   

}

/*RPC服务端流程
    启动的时候就注册OrderService对象。

    1. 从buffer读取数据，然后 decode 得到请求的 TinyPBProtocol 对象。然后从请求的 TinyPBProtocol 得到 method_name, 从 OrderService 对象里根据 service.method_name 找到方法 func
    2. 找到对应的 requeset type 以及 response type
    3. 将请求体 TinyPBProtobol 里面的 pb_data 反序列化为 requeset type 的一个对象, 声明一个空的 response type 对象
    4. func(request, response)      callMethod方法
    5. 将 reponse 对象序列为 pb_data。 再塞入到 TinyPBProtocol 结构体中。做 encode 然后塞入到buffer里面，就会发送回包了*/
