#include<sys/socket.h>
#include<fcntl.h>
#include<string>
#include<pthread.h>
#include<memory>
#include<functional>
#include<unistd.h>
#include<google/protobuf/service.h>
#include "rocket/net/tcp/net_addr.h"
#include "rocket/common/log.h"
#include"rocket/net/tcp/tcp_server.h"
#include "rocket/net/tcp/tcp_client.h"
#include "rocket/net/coder/string_coder.h"
#include"rocket/net/coder/abstract_protocol.h"
#include "rocket/net/coder/tinypb_coder.h"
#include "order.pb.h"
#include"rocket/net/rpc/rpc_channel.h"
#include"rocket/net/rpc/rpc_controller.h"
#include "rocket/net/rpc/rpc_closure.h"

void test_client(){
    auto addr=std::make_shared<rocket::IPNetAddr>("127.0.0.1",12345);
    rocket::TcpClient client(addr);
    client.connect([addr,&client](){
      LOG_DEBUG("connect to [%s] success",addr->toString().c_str());
      std::shared_ptr<rocket::TinyPBProtocol>message=std::make_shared<rocket::TinyPBProtocol>();
      message->m_msgId="99998888";
      message->m_pb_data="test pb data";

      makeOrderRequest request;
      request.set_price(100);
      request.set_goods("apple");
      if(!request.SerializeToString(&(message->m_pb_data))){
        LOG_ERROR("serialize error");
        return;
      }

      message->m_method_name="Order.makeorder";

      client.writeMessage(message,[request](rocket::AbstractProtocol::ptr msg_ptr){
        LOG_DEBUG("send message success,request[%s]",request.ShortDebugString().c_str());
      });

      client.readMessage("99998888",[](rocket::AbstractProtocol::ptr msg_ptr){
        std::shared_ptr<rocket::TinyPBProtocol>message=std::dynamic_pointer_cast<rocket::TinyPBProtocol>(msg_ptr);
        LOG_DEBUG("req_id [%s],get response %s success",message->m_msgId.c_str(),message->m_pb_data.c_str());
        makeOrderResponse response;

        if(!response.ParseFromString(message->m_pb_data)){
          LOG_ERROR("deserialize error");
        }
        LOG_DEBUG("get response success,response[%s]",response.ShortDebugString().c_str());
      });

    });
}


void test_rpc_channel(){

  NEWRPCCHANNEL("127.0.0.1:12345",channel);
  NEWMESSAGE(makeOrderRequest,request);
  NEWMESSAGE(makeOrderResponse,response);

  request->set_price(100);
  request->set_goods("apple");


  NEWCONTROLLER(controller);

  controller->SetmsgId("99998888");
  std::shared_ptr<rocket::RpcClosure> closure=std::make_shared<rocket::RpcClosure>([request,response,channel,controller]() mutable{
    if(controller->GetErrorCode()==0){
        LOG_INFO("call rpc success,request[%s],response[%s]"
        ,request->ShortDebugString().c_str(),response->ShortDebugString().c_str());

        //执行业务逻辑
        if(response->order_id()=="xxx"){

        }
    }else{
        LOG_INFO("call rpc failed,request[%s],error code[%d],error info[%s]"
        ,request->ShortDebugString().c_str(),controller->GetErrorCode(),controller->GetErrorInfo().c_str());
    }
    

    LOG_INFO("now exit eventloop");
    channel->getTcpClient()->stop();
    channel.reset();
  });

  CALLRPC("127.0.0.1:12345",makeOrder,controller,request,response,closure);

}

int main(int argc,char** argv){

    rocket::Config::setGlobalConfig("conf/rocket.xml");
    rocket::Logger::InitGlobalLogger();

    test_client();
    return 0;
}