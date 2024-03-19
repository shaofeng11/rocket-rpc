#include<sys/socket.h>
#include<fcntl.h>
#include<string>
#include<pthread.h>
#include<memory>
#include<functional>
#include<unistd.h>
#include "rocket/net/tcp/net_addr.h"
#include "rocket/common/log.h"
#include"rocket/net/tcp/tcp_server.h"
#include "rocket/net/tcp/tcp_client.h"
#include "rocket/net/coder/string_coder.h"
#include"rocket/net/coder/abstract_protocol.h"
#include "rocket/net/coder/tinypb_coder.h"

void test_connect(){
  // 调用 conenct 连接 server
  // wirte 一个字符串
  // 等待 read 返回结果

  int fd = socket(AF_INET, SOCK_STREAM, 0);

  if (fd < 0) {
    LOG_ERROR("invalid fd %d", fd);
    exit(0);
  }

  sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(12345);
  inet_aton("127.0.0.1", &server_addr.sin_addr);

  int rt = connect(fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));

  LOG_DEBUG("connect success");

  std::string msg = "hello rocket!";
  
  rt = write(fd, msg.c_str(), msg.length());
  LOG_DEBUG("rt=%d",rt);
  LOG_DEBUG("success write %d bytes, [%s]", rt, msg.c_str());

  char buf[100];
  rt = read(fd, buf, 100);
  LOG_DEBUG("success read %d bytes, [%s]", rt, std::string(buf).c_str()); 
}

void test_client(){
    auto addr=std::make_shared<rocket::IPNetAddr>("127.0.0.1",12345);
    rocket::TcpClient client(addr);
    client.connect([addr,&client](){
      LOG_DEBUG("connect to [%s] success",addr->toString().c_str());
      std::shared_ptr<rocket::TinyPBProtocol>message=std::make_shared<rocket::TinyPBProtocol>();
      message->m_msgId="123456789";
      message->m_pb_data="test pb data";

    //客户端流程：1.client将message写入对端服务器，将message对象以及回调函数写入到m_write_dones,注册可写事件
          //2.触发可写事件，调用onWrite，判断connectionType==TcpConnectionByClient?
          //将message编码，写入到m_out_buffer,然后将其中所有数据调用write发送到client。发送完之后执行m_write_dones中的回调函数

    //1.将req_id以及回调函数注册到m_read_dones,注册可读事件
    //2.2.触发可读事件，调用onRead，将所有数据读到m_in_buffer，执行excute()
    //3.判断如果connectionType==TcpConnectionByClient，将inbuffer中的数据decode()解码，得到req_id,根据req_id执行回调
      client.writeMessage(message,[](rocket::AbstractProtocol::ptr msg_ptr){
        LOG_DEBUG("send message success");
      });

      client.readMessage("123456789",[](rocket::AbstractProtocol::ptr msg_ptr){
        std::shared_ptr<rocket::TinyPBProtocol>message=std::dynamic_pointer_cast<rocket::TinyPBProtocol>(msg_ptr);
        LOG_DEBUG("req_id [%s],get response %s success",message->m_msgId.c_str(),message->m_pb_data.c_str());
      });

    });
}

int main(int argc,char** argv){

    rocket::Config::setGlobalConfig("conf/rocket.xml");
    rocket::Logger::InitGlobalLogger();
    
    //test_connect();
    test_client();
    return 0;
}