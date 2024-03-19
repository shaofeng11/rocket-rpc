#ifndef ROCKET_NET_TINYPB_CODER_H__
#define ROCKET_NET_TINYPB_CODER_H__

#include"abstract_coder.h"
#include "tinypb_protocol.h"

namespace rocket{

class TinyPBCoder:public AbstractCoder{
      //将message对象转化为字节流，写入到buffer
    void encode(std::vector<AbstractProtocol::ptr>& message,TcpBuffer::ptr buffer) override;

    //将buffer里面的字节流转化为message对象
    void decode(std::vector<AbstractProtocol::ptr>& out_message,TcpBuffer::ptr out_buffer) override;

private:
    const char* encodeTinyPB(std::shared_ptr<TinyPBProtocol> messagge,int& len);
};
}

#endif