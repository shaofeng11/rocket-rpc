#ifndef ROCKET_RPC_RPC_CHANNEL
#define ROCKET_RPC_RPC_CHANNEL

#include <google/protobuf/service.h>
#include"rpc_controller.h"
#include"../tcp/net_addr.h"
#include"../tcp/tcp_client.h"
#include"../timer.h"
namespace rocket{

#define NEWMESSAGE(type,var_name) \
    std::shared_ptr<type> var_name=std::make_shared<type>(); \

#define NEWCONTROLLER(var_name) \
    std::shared_ptr<rocket::RpcController> var_name=std::make_shared<rocket::RpcController>(); \

#define NEWRPCCHANNEL(addr,var_name) \
      std::shared_ptr<rocket::RpcChannel>var_name=std::make_shared<rocket::RpcChannel>(std::make_shared<rocket::IPNetAddr>(addr)); \

#define CALLRPC(addr,method_name,contorller,request,response,closure) \
  { \
    NEWRPCCHANNEL(addr,channel); \
    channel->Init(controller,request,response,closure); \
    Order_Stub(channel.get()).method_name(controller.get(),request.get(),response.get(),closure.get()); \
  } \


  
class RpcChannel :public google::protobuf::RpcChannel,public std::enable_shared_from_this<RpcChannel>{

public:
    typedef std::shared_ptr<RpcChannel>ptr;
    typedef std::shared_ptr<google::protobuf::RpcController>controller_ptr;
    typedef std::shared_ptr<google::protobuf::Message>message_ptr;
    typedef std::shared_ptr<google::protobuf::Closure>closure_ptr;
public:

    RpcChannel(NetAddr::ptr peer_addr);
    ~RpcChannel(){}

    void Init(controller_ptr controller,message_ptr req,message_ptr res,closure_ptr closure);

    void CallMethod(const google::protobuf::MethodDescriptor* method,
                    google::protobuf::RpcController* controller, const google::protobuf::Message* request,
                    google::protobuf::Message* response, google::protobuf::Closure* done);
    google::protobuf::RpcController* getController() const {return m_controller.get();}
    google::protobuf::Message* getRequest() const {return m_request.get();}
    google::protobuf::Message* getResponse() const {return m_response.get();}
    google::protobuf::Closure* getClosure() const {return m_closure.get();}

    TcpClient* getTcpClient() const {return m_client.get();}

    TimerEvent::ptr getTimerEvent() const{ return m_timer_event;}
private:
    NetAddr::ptr m_peerAddr{nullptr};
    NetAddr::ptr m_localAddr{nullptr};

    controller_ptr m_controller{nullptr};
    message_ptr m_request{nullptr};
    message_ptr m_response{nullptr};
    closure_ptr m_closure{nullptr};

    bool m_is_init{false};

    TcpClient::ptr m_client{nullptr};
    TimerEvent::ptr m_timer_event{nullptr};
};

}

#endif