#include "rpc_controller.h"

namespace rocket{

void RpcController::Reset() {
    m_error_code=0;
    m_errorInfo="";
    m_msgId="";

    m_is_failed=false;
    m_is_canceled=false;
    m_localAddr=nullptr;
    m_peerAddr=nullptr;
    m_timeout=1000;
}

bool RpcController::Failed() const{
    return m_is_failed;
}

std::string RpcController::ErrorText() const{
    return m_errorInfo;
}

void RpcController::StartCancel(){
    m_is_canceled=true;
}

void RpcController::SetFailed(const std::string& reason){
    m_errorInfo=reason;
}

bool RpcController::IsCanceled() const{
    return m_is_canceled;
}

void RpcController::NotifyOnCancel(google::protobuf::Closure* callback){

}

}