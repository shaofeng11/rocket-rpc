#ifndef ROCKET_NET_STRING_CODER_H__
#define ROCKET_NET_STRING_CODER_H__

#include"abstract_coder.h"
#include"abstract_protocol.h"

namespace rocket{

class StringProtocol:public AbstractProtocol{
public:
    std::string info;
};
    

class StringCoder:public AbstractCoder{
    ~StringCoder(){}
     //将message对象转化为字节流，写入到buffer
    void encode(std::vector<AbstractProtocol::ptr>& message,TcpBuffer::ptr out_buffer){
        for(size_t i=0;i<message.size();++i){
            std::shared_ptr<StringProtocol> msg=std::dynamic_pointer_cast<StringProtocol>(message[i]);
            out_buffer->writeToBuffer(msg->info.c_str(),msg->info.length());
        }
    }

    //将buffer里面的字节流转化为message对象
    void decode(std::vector<AbstractProtocol::ptr>& out_message,TcpBuffer::ptr buffer){
        std::vector<char>re;
        buffer->readFromBuffer(re,buffer->readAble());
        std::string info;
        for(size_t i=0;i<re.size();++i){
            info+=re[i];
        }
        std::shared_ptr<StringProtocol> msg = std::make_shared<StringProtocol>();
        msg->info=info;
        //msg->setmsgId("123456");
        out_message.push_back(msg);
    }
};
}

#endif