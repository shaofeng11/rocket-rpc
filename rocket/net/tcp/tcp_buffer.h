#ifndef ROCKET_NET_TCP_TCPBUFFER_H__
#define ROCKET_NET_TCP_TCPBUFFER_H__

#include<vector>
#include<memory>
namespace rocket{
class TcpBuffer{
public:
    typedef std::shared_ptr<TcpBuffer>ptr;

    TcpBuffer(int size);
    ~TcpBuffer();
    int readAble();
    int writeAble();

    int getReadIndex();
    int getWriteIndex();


    void writeToBuffer(const char* buf,int size);

    void readFromBuffer(std::vector<char>& re,int size);

    void resizeBuffer(int size);

    void adjustBuffer();

    void moveReadIndex(int size);

    void moveWriteIndex(int size);
private:
    int m_readIndex{0};
    int m_writeIndex{0};
    int m_size{0};

public:
    std::vector<char>m_buffer;
};


}

#endif