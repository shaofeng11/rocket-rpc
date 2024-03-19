#ifndef ROCKET_NET_ABSTRACT_CODER_H__
#define ROCKET_NET_ABSTRACT_CODER_H__

#include<vector>
#include "../tcp/tcp_buffer.h"
#include "abstract_protocol.h"

namespace rocket{
class AbstractCoder{

public:
    virtual ~AbstractCoder(){}

    //将message对象转化为字节流，写入到buffer
    virtual void encode(std::vector<AbstractProtocol::ptr>& message,TcpBuffer::ptr buffer)=0;

    //将buffer里面的字节流转化为message对象
    virtual void decode(std::vector<AbstractProtocol::ptr>& out_message,TcpBuffer::ptr out_buffer)=0;

    
};

}

#endif
