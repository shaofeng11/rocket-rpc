#include<google/protobuf/descriptor.h>
#include<google/protobuf/message.h>
#include "rpc_channel.h"
#include"../../common/log.h"
#include"../coder/tinypb_protocol.h"
#include"../../common/msgId_util.h"
#include"../tcp/tcp_client.h"
#include "../../common/error_code.h"
namespace rocket{

RpcChannel::RpcChannel(NetAddr::ptr peer_addr){
    m_client=std::make_shared<TcpClient>(m_peerAddr);
}


void RpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                    google::protobuf::RpcController* controller, const google::protobuf::Message* request,
                    google::protobuf::Message* response, google::protobuf::Closure* done){
    std::shared_ptr<TinyPBProtocol>req_protocol=std::make_shared<TinyPBProtocol>();
   
    RpcController* my_controller=dynamic_cast<RpcController*>(controller);


    if(my_controller==NULL||request==NULL|| response==NULL){
        LOG_ERROR("failed callmethod,RpcController convert error");
        return;
    }



    if(my_controller->GetmsgId().empty()){
        req_protocol->m_msgId=MsgIdUtil::GetMsgId();
        my_controller->SetmsgId(req_protocol->m_msgId);
    }
    req_protocol->m_msgId=my_controller->GetmsgId();


    req_protocol->m_method_name=method->full_name();
    LOG_INFO("%s | call method name [%s]",req_protocol->m_msgId.c_str(),req_protocol->m_method_name.c_str());


    if(!m_is_init){
        std::string err_info="RpcChannel not init";
        my_controller->SetError(ERROR_RPC_CHANNEL_INIT,err_info);
        LOG_ERROR("%s | %s, origin requeset [%s] ", req_protocol->m_msgId.c_str(), err_info.c_str(), request->ShortDebugString().c_str());
        return;
    }

    //request的序列化
    if(!request->SerializeToString(&(req_protocol->m_pb_data))){
        std::string err_info="failed to serialize";
        my_controller->SetError(ERROR_FAILED_SERIALIZE,err_info);
        LOG_ERROR("%s | %s, origin requeset [%s] ", req_protocol->m_msgId.c_str(), err_info.c_str(), request->ShortDebugString().c_str());
        return;
    }

    RpcChannel::ptr channel=shared_from_this();

    m_timer_event=std::make_shared<TimerEvent>(my_controller->GetTimeout(),false,[my_controller,channel]() mutable{
        my_controller->StartCancel();
        my_controller->SetError(ERROR_RPC_CALL_TIMEOUT,"rpc call timeout" +std::to_string(my_controller->GetTimeout()));

        if(channel->getClosure()){
            channel->getClosure()->Run();
        }
        channel.reset();
    });
    //将定时任务添加到epoll上 
    channel->getTcpClient()->addTimerEvent(m_timer_event);

    m_client->connect([req_protocol,channel,my_controller]() mutable{

        if(channel->getTcpClient()->getConnectErrorCode()!=0){
                LOG_ERROR("%s | connect error,error code[%d],error info[%s],peer addr[%s]",
                            req_protocol->m_msgId.c_str(),my_controller->GetErrorCode(),
                            my_controller->GetErrorInfo().c_str(),channel->getTcpClient()->getPeerAddr()->toString().c_str());
                my_controller->SetError(channel->getTcpClient()->getConnectErrorCode(),channel->getTcpClient()->getConnectErrorInfo().c_str());
                return;
        }

        channel->getTcpClient()->writeMessage(req_protocol,[req_protocol,channel,my_controller](AbstractProtocol::ptr) mutable{
            LOG_INFO("%s |, send rpc request success,method_name [%s],peer addr[%s],local addr[%s]",
                    req_protocol->m_msgId.c_str(),req_protocol->m_method_name.c_str(),
                    channel->getTcpClient()->getPeerAddr()->toString().c_str(),channel->getTcpClient()->getLocalAddr()->toString().c_str())
            channel->getTcpClient()->readMessage(req_protocol->m_msgId,[channel,my_controller](AbstractProtocol::ptr msg) mutable{
                std::shared_ptr<rocket::TinyPBProtocol>rsp_protocol=std::dynamic_pointer_cast<rocket::TinyPBProtocol>(msg);
                LOG_INFO("%s |,success get rpc response,call method name [%s]" ,
                    rsp_protocol->m_msgId.c_str(),rsp_protocol->m_method_name.c_str());
                
                //当成功读取到回包后，取消定时任务
                channel->getTimerEvent()->setCancel(true);

                
                if(!channel->getResponse()->ParseFromString(rsp_protocol->m_pb_data)){
                    LOG_ERROR("%s | serialize error",rsp_protocol->m_msgId.c_str());
                    my_controller->SetError(ERROR_FAILED_SERIALIZE,"serialize error");
                    return;
                }

                if(rsp_protocol->m_err_code!=0){
                    LOG_ERROR("%s | call rpc method[%s] failed,error code[%d],error info[%s]",
                                rsp_protocol->m_msgId.c_str(),rsp_protocol->m_method_name.c_str(),
                                rsp_protocol->m_err_code,rsp_protocol->m_err_info.c_str());
                    my_controller->SetError(rsp_protocol->m_err_code,rsp_protocol->m_err_info);
                    return;
                } 

                LOG_INFO("%s | call rpc success,call method name[%s],peer addr[%s],local addr[%s]",
                            rsp_protocol->m_msgId.c_str(),rsp_protocol->m_method_name.c_str(),
                            channel->getTcpClient()->getPeerAddr()->toString().c_str()
                            ,channel->getTcpClient()->getLocalAddr()->toString().c_str());

                if(!my_controller->IsCanceled() && channel->getClosure()){
                    channel->getClosure()->Run();
                }
                channel.reset();
            });
        });
    });
}

void RpcChannel::Init(controller_ptr controller,message_ptr req,message_ptr res,closure_ptr closure){
    if(m_is_init){
        return;
    }
    m_controller=controller;
    m_request=req;
    m_response=res;
    m_closure=closure;
    m_is_init=true;
}


}