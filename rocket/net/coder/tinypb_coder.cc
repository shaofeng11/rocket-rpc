#include<stdlib.h>
#include<arpa/inet.h>
#include "tinypb_coder.h"
#include "tinypb_protocol.h"
#include "../../common/util.h"
#include "../../common/log.h"
namespace rocket{

const char* TinyPBCoder::encodeTinyPB(std::shared_ptr<TinyPBProtocol> message,int& len){
    if(message->m_msgId.empty()){
        message->m_msgId="123456789";  
    }
    LOG_DEBUG( "req_id = %s",message->m_msgId.c_str());
    int pk_len=2+24+message->m_err_info.length()+message->m_method_name.length()+message->m_msgId.length()+message->m_pb_data.length();
    LOG_DEBUG("pk_len = %",pk_len);

    char* buf=reinterpret_cast<char*>(malloc(pk_len));
    char* tmp=buf;
    *tmp=TinyPBProtocol::PB_START;
    tmp++;

    int32_t pk_len_net=htonl(pk_len);
    memcpy(tmp,&pk_len_net,sizeof(pk_len_net));

    tmp+=sizeof(pk_len_net);

    int req_id_len=message->m_msgId.length();
    int32_t req_id_len_net=htonl(req_id_len);
    memcpy(tmp,&req_id_len_net,sizeof(req_id_len_net));

    tmp+=sizeof(req_id_len_net);

    if(!message->m_msgId.empty()){
        memcpy(tmp,&(message->m_msgId[0]),req_id_len);
        tmp+=req_id_len;
    }

    int method_name_len = message->m_method_name.length();
    int32_t method_name_len_net = htonl(method_name_len);
    memcpy(tmp, &method_name_len_net, sizeof(method_name_len_net));
    tmp += sizeof(method_name_len_net);


    if (!message->m_method_name.empty()) {
        memcpy(tmp, &(message->m_method_name[0]), method_name_len);
        tmp += method_name_len;
    }

    int32_t err_code_net = htonl(message->m_err_code);
    memcpy(tmp, &err_code_net, sizeof(err_code_net));
    tmp += sizeof(err_code_net);

    int err_info_len = message->m_err_info.length();
    int32_t err_info_len_net = htonl(err_info_len);
    memcpy(tmp, &err_info_len_net, sizeof(err_info_len_net));
    tmp += sizeof(err_info_len_net);

    if (!message->m_err_info.empty()) {
        memcpy(tmp, &(message->m_err_info[0]), err_info_len);
        tmp += err_info_len;
    }

    if (!message->m_pb_data.empty()) {
        memcpy(tmp, &(message->m_pb_data[0]), message->m_pb_data.length());
        tmp += message->m_pb_data.length();
    }

    int32_t check_sum_net = htonl(1);
    memcpy(tmp, &check_sum_net, sizeof(check_sum_net));
    tmp += sizeof(check_sum_net);

    *tmp = TinyPBProtocol::PB_END;

    message->m_pk_len = pk_len;
    message->m_req_id_len = req_id_len;
    message->m_method_name_len = method_name_len;
    message->m_err_info_len = err_info_len;
    message->m_parser_success = true;
    len = pk_len;

    LOG_DEBUG("encode message[%s] success", message->m_msgId.c_str());

    return buf;

}

void  TinyPBCoder::encode(std::vector<AbstractProtocol::ptr>& message,TcpBuffer::ptr buffer) {
    for(auto& i:message){
      std::shared_ptr<TinyPBProtocol> msg=std::dynamic_pointer_cast<TinyPBProtocol>(i);  
      int len=0;
      const char* buf=encodeTinyPB(msg,len); 
      if(buf != NULL && len != 0) {
        buffer->writeToBuffer(buf, len);
      }
      if(buf) {
            free((void*)buf);
            buf = NULL;
     } 
    } 
}

//将buffer里面的字节流转化为message对象
void TinyPBCoder::decode(std::vector<AbstractProtocol::ptr>& out_message,TcpBuffer::ptr out_buffer){
    LOG_DEBUG("decode");
    //遍历buffer，找到PB_START,解析出整包长度。然后得到结束符位置，判断是否为PB_END
    while(1){
        std::vector<char>tmp=out_buffer->m_buffer;
        int start_index=out_buffer->getReadIndex();
        int end_index=-1;

        int pk_len=0;
        bool parse_success=false;
        int i=0;
        for(i=start_index;i<out_buffer->getWriteIndex();++i){
            if(tmp[i]==TinyPBProtocol::PB_START){
                //从下取四个字节，由于是网络字节序，需转化为主机字节序
                if(i+1<out_buffer->getWriteIndex()){
                    pk_len=getInt32FromNetByte(&tmp[i+1]);
                    LOG_DEBUG("get pk_len=%d",pk_len);

                    //结束符索引
                    int j=i+pk_len-1;
                    if(j>=out_buffer->getWriteIndex()){
                        continue;
                    }
                    if(tmp[j]==TinyPBProtocol::PB_END){
                        start_index=i;
                        end_index=j;
                        parse_success=true;
                        break;
                    }
                }
            }
        }

        if(i>=out_buffer->getWriteIndex()){
            LOG_DEBUG("decode end,read all buffer data");
            return;
        }
        if(parse_success==true){
            out_buffer->moveReadIndex(end_index-start_index+1);
            std::shared_ptr<TinyPBProtocol> message=std::make_shared<TinyPBProtocol>();
            message->m_pk_len=pk_len;

            int req_id_len_index=start_index+sizeof(char)+sizeof(message->m_pk_len);
            if(req_id_len_index>=end_index){
                message->m_parser_success=false;
                LOG_ERROR("parser error,req_id_len_index[%d]>=end_index[%d]",req_id_len_index,end_index);
                continue;
            }
            message->m_req_id_len=getInt32FromNetByte(&tmp[req_id_len_index]);
            LOG_DEBUG("parser req_id_len=%d",message->m_req_id_len);

            int req_id_index=req_id_len_index+sizeof(message->m_req_id_len);

            char req_id[100]={0};
            memcpy(&req_id[0],&tmp[req_id_index],message->m_req_id_len);
            message->m_msgId=std::string(req_id);

            LOG_DEBUG("parse req_id=%s",message->m_msgId.c_str());
            int method_name_len_index=req_id_index+message->m_req_id_len;
            if(method_name_len_index>=end_index){
                message->m_parser_success=false;
                LOG_ERROR("parser error,method_name_len_index[%d]>=end_index[%d]",method_name_len_index,end_index);
                continue;
            }

            message->m_method_name_len=getInt32FromNetByte(&tmp[method_name_len_index]);

            int method_name_index=method_name_len_index+sizeof(message->m_method_name_len);
            char method_name[100]={0};
            memcpy(&method_name[0],&tmp[method_name_index],message->m_method_name_len);
            message->m_method_name=std::string(method_name);
            LOG_DEBUG("parse method_name=%s",message->m_method_name.c_str());

            int error_code_index=method_name_index+message->m_method_name_len;
            if(error_code_index>=end_index){
                message->m_parser_success=false;
                LOG_ERROR("parser error,error_code_index[%d]>=end_index[%d]",error_code_index,end_index);
                continue;
            }
            message->m_err_code=getInt32FromNetByte(&tmp[error_code_index]);

            int error_info_len_index=error_code_index+sizeof(message->m_err_code);
            if( error_info_len_index>=end_index){
                message->m_parser_success=false;
                LOG_ERROR("parser error, error_info_len_index[%d]>=end_index[%d]", error_info_len_index,end_index);
                continue;
            }

            message->m_err_info_len=getInt32FromNetByte(&tmp[error_info_len_index]);

            int error_info_index=error_info_len_index+sizeof(message->m_err_info_len);
            char error_info[100]={0};
            memcpy(&error_info[0],&tmp[error_info_index],message->m_err_info_len);
            message->m_err_info=std::string(error_info);
            LOG_DEBUG("parse error_info=%s",message->m_err_info.c_str());

            int pb_data_len=message->m_pk_len-message->m_method_name_len-message->m_req_id_len-message->m_err_info_len-2-24;
            int pb_data_index=error_info_index+message->m_err_info_len;

            message->m_pb_data=std::string(&tmp[pb_data_index],pb_data_len);

            //校验和去解析

            message->m_parser_success=true;

            out_message.push_back(message);
        }
    }
}
}