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

class OrderImpl:public Order{
public:
    virtual void makeOrder(google::protobuf::RpcController* controller,
                    const ::makeOrderRequest* request,
                    ::makeOrderResponse* response,
                    ::google::protobuf::Closure* done){
        LOG_DEBUG("start sleep 5s");
        sleep(5);
        LOG_DEBUG("end sleep 5s");
        //业务逻辑
        if(request->price()<10){
            response->set_ret_code(-1);
            response->set_res_info("short balance");
            return;
        }
        response->set_order_id("20230514");
    }
};


void test_tcp_server() {
    auto addr=std::make_shared<rocket::IPNetAddr>("127.0.0.1",12345);
    LOG_DEBUG("create addr %s",addr->toString().c_str());
    rocket::TcpServer tcp_server(addr);

    tcp_server.start();
}


int main(int argc,char** argv){

    rocket::Config::setGlobalConfig("conf/rocket.xml");
    rocket::Logger::InitGlobalLogger();
    
    
    std::shared_ptr<OrderImpl> service=std::make_shared<OrderImpl>();
    rocket::RpcDispatcher::GetRpcDispatcher()->registerService(service);

    test_tcp_server();
    return 0;
}

//将service对象注册到rpc服务，然后启动rpc服务