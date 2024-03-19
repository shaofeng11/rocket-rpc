
#ifndef ROCKET_NET_RPC_RPC_CONTROLLER_H__
#define ROCKET_NET_RPC_RPC_CONTROLLER_H__
#include<google/protobuf/stubs/callback.h>
#include <google/protobuf/service.h>
#include "../tcp/net_addr.h"

namespace rocket{

class RpcController:public google::protobuf::RpcController{
public:
    RpcController(){}
    ~RpcController(){}

    virtual void Reset() override;

    virtual bool Failed() const  override;

    virtual std::string ErrorText() const  override;

    virtual void StartCancel() override;

    virtual void SetFailed(const std::string& reason)  override;

    virtual bool IsCanceled() const  override;

    virtual void NotifyOnCancel(google::protobuf::Closure* callback) override;

    void SetError(int32_t error_code,const std::string& error_info){ m_error_code=error_code; m_errorInfo=error_info; m_is_failed=true;}

    int32_t GetErrorCode()const { return m_error_code;}

    std::string GetErrorInfo() const {return m_errorInfo;}

    void SetmsgId(const std::string req_id) { m_msgId=req_id;}

    std::string GetmsgId() const { return m_msgId;}

    void SetLocalAddr(NetAddr::ptr addr){ m_localAddr=addr;}

    void SetPeerAddr(NetAddr::ptr addr){ m_peerAddr=addr;}

    NetAddr::ptr GetLocalAddr() const{ return m_localAddr;}

    NetAddr::ptr GetPeerAddr() const{ return m_peerAddr;}

    void SetTimeout(int timeout){ m_timeout=timeout;}

    int GetTimeout() const {return m_timeout;}
private:
    int32_t m_error_code{0};
    std::string m_errorInfo;
    std::string m_msgId;

    bool m_is_failed{false};
    bool m_is_canceled{false};

    NetAddr::ptr m_localAddr;
    NetAddr::ptr m_peerAddr;

    int m_timeout{1000};
};
}


#endif