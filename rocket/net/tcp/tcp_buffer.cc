#include<unistd.h>
#include<memory>
#include<string.h>
#include "tcp_buffer.h"
#include "rocket/common/log.h"
namespace rocket{
TcpBuffer::TcpBuffer(int size):m_size(size){
    m_buffer.resize(size);
}
TcpBuffer::~TcpBuffer(){

}
int TcpBuffer::readAble(){
    return m_writeIndex-m_readIndex;
}
int TcpBuffer::writeAble(){
    return m_buffer.size()-m_writeIndex;
}

int TcpBuffer::getReadIndex(){
    return m_readIndex;
}
int TcpBuffer::getWriteIndex(){
    return m_writeIndex;
}


void TcpBuffer::writeToBuffer(const char* buf,int size){
    if(size>writeAble()){
        //扩容
        int new_size=int(1.5*(m_writeIndex+size));
        resizeBuffer(new_size);   
    }
    memcpy(&m_buffer[m_writeIndex],buf,size);

    m_writeIndex+=size;
}

void TcpBuffer::readFromBuffer(std::vector<char>& re,int size){
    if(readAble()==0){
        return;
    }
    int read_size=readAble()>size?size:readAble();
    std::vector<char>tmp(read_size);
    memcpy(&tmp[0],&m_buffer[m_readIndex],read_size);
    re.swap(tmp);
    m_readIndex+=read_size;

    adjustBuffer();
}


void TcpBuffer::resizeBuffer(int size){
    std::vector<char>tmp(size);
    int count=std::min(size,readAble());

    memcpy(&tmp[0],&m_buffer[m_readIndex],count);
    m_buffer.swap(tmp);

    m_readIndex=0;
    m_writeIndex=m_readIndex+count;
}

void  TcpBuffer::adjustBuffer(){
    if(m_readIndex<int(m_buffer.size()/3)){
        return;
    }
    std::vector<char>tmp(m_buffer.size());
    int count=readAble();

    memcpy(&tmp[0],&m_buffer[m_readIndex],count);

    m_buffer.swap(tmp);
    m_readIndex=0;
    m_writeIndex=count;
    tmp.clear();
}


void TcpBuffer::moveReadIndex(int size){
    size_t j=m_readIndex+size;
    if(j>=m_buffer.size()){
        LOG_ERROR("moveReadIndex error,invalid size %d,old_read_index %d,buffer size %d"
                    ,size,m_readIndex,m_buffer.size());
    }
    m_readIndex=j;
    adjustBuffer();
}

void TcpBuffer::moveWriteIndex(int size){
    size_t j=m_writeIndex+size;
    if(j>=m_buffer.size()){
        LOG_ERROR("moveReadIndex error,invalid size %d,old_write_index %d,buffer size %d"
                    ,size,m_writeIndex,m_buffer.size());
    }
    m_writeIndex=j;
    adjustBuffer();
}
}