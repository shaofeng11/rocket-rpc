#ifndef ROCKET_NET_TCP_ABSTRACT_PROTOCOL_H__
#define ROCKET_NET_TCP_ABSTRACT_PROTOCOL_H__
#include<memory>
#include<string>
#include"../tcp/tcp_buffer.h"
namespace rocket{

struct AbstractProtocol:public std::enable_shared_from_this<AbstractProtocol>{
public:
    typedef std::shared_ptr<AbstractProtocol>ptr;
    virtual ~AbstractProtocol(){}

    //void setmsgId(std::string msgId) {m_msgId=msgId;}
    //std::string getmsgId() const{ return m_msgId;}
public:
    std::string m_msgId;  //    请求号，唯一标识一个请求或者响应    
};


}

#endif