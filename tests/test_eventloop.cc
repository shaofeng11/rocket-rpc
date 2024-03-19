#include "rocket/common/log.h"
#include"rocket/common/config.h"
#include"rocket/net/eventLoop.h"
#include"rocket/net/timer_event.h"
#include"rocket/net/io_thread.h"
#include"rocket/net/io_thread_group.h"
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<memory>

void test_ioThread(){
    int listenfd=socket(AF_INET,SOCK_STREAM,0);
    if(listenfd==-1){
        LOG_ERROR("listenfd=-1");
        exit(0);
    }
    LOG_INFO("listen fd=%d",listenfd);
    sockaddr_in addr;
    memset(&addr,0,sizeof(addr));

    inet_aton("127.0.0.1",&addr.sin_addr);
    addr.sin_family=AF_INET;
    addr.sin_port=htons(12346);

    //将listenfd绑定到本机地址，端口号12346
    int rt=bind(listenfd,(sockaddr*)&addr,sizeof(addr));
    if(rt!=0){
        LOG_ERROR("bind error");
        exit(1);
    }
    //开始监听
    rt=listen(listenfd,100);
    if(rt!=0){
        LOG_ERROR("listen error");
        exit(1);
    }

    rocket::FdEvent event(listenfd);

    //给事件添加回调
    event.listen(rocket::FdEvent::IN_EVENT,[listenfd](){
        sockaddr_in peer_addr;
        socklen_t addr_len=sizeof(peer_addr);
        memset(&peer_addr,0,addr_len);
        int clientfd=accept(listenfd,(sockaddr*)&peer_addr,&addr_len);

        
        LOG_DEBUG("success get client fd[%d],peer addr:[%s:%d]",clientfd,inet_ntoa(peer_addr.sin_addr),ntohs(peer_addr.sin_port));
    });

    int i=0;

    //定时任务，循环定时器，每次i+1
    rocket::TimerEvent::ptr timer_event=std::make_shared<rocket::TimerEvent>(1000,true,[&i](){
        LOG_INFO("trigger timer event,count=%d",i++);
    });
    // rocket::IOThread io_thread;

    // io_thread.getEventLoop()->addEpollEvent(&event);
    // io_thread.getEventLoop()->addTimerEvent(timer_event);
    // io_thread.start();
    // io_thread.join();
    rocket::IOThreadGroup io_thread_group(2);
    //取第一个线程
    rocket::IOThread* io_thread=io_thread_group.getIOThread();

    //先添加时间再开启loop循环
    io_thread->getEventLoop()->addEpollEvent(&event);
    io_thread->getEventLoop()->addTimerEvent(timer_event);

    //取第二个io线程
    rocket::IOThread* io_thread2=io_thread_group.getIOThread();
    io_thread2->getEventLoop()->addTimerEvent(timer_event);

    //开始loop循环
    io_thread_group.start();

    //回收线程
    io_thread_group.join();
}

int main(int argc,char** argv){

    rocket::Config::setGlobalConfig("conf/rocket.xml");
    rocket::Logger::InitGlobalLogger();
    test_ioThread();
    
    // rocket::EventLoop* eventLoop=new rocket::EventLoop();

    // int listenfd=socket(AF_INET,SOCK_STREAM,0);
    // if(listenfd==-1){
    //     LOG_ERROR("listenfd=-1");
    //     exit(0);
    // }

    // sockaddr_in addr;
    // memset(&addr,0,sizeof(addr));

    // inet_aton("127.0.0.1",&addr.sin_addr);
    // addr.sin_family=AF_INET;
    // addr.sin_port=htons(12345);

    // int rt=bind(listenfd,(sockaddr*)&addr,sizeof(addr));
    // if(rt!=0){
    //     LOG_ERROR("bind error");
    //     exit(1);
    // }
    // rt=listen(listenfd,100);
    // if(rt!=0){
    //     LOG_ERROR("listen error");
    //     exit(1);
    // }

    // rocket::FdEvent event(listenfd);
    // event.listen(rocket::FdEvent::IN_EVENT,[listenfd](){
    //     sockaddr_in peer_addr;
    //     socklen_t addr_len=sizeof(peer_addr);
    //     memset(&peer_addr,0,addr_len);
    //     int clientfd=accept(listenfd,(sockaddr*)&peer_addr,&addr_len);

        
    //     LOG_DEBUG("success get client fd[%d],peer addr:[%s:%d]",clientfd,inet_ntoa(peer_addr.sin_addr),ntohs(peer_addr.sin_port));
    // });
    // eventLoop->addEpollEvent(&event);

    // int i=0;
    // rocket::TimerEvent::ptr timer_event=std::make_shared<rocket::TimerEvent>(1000,true,[&i](){
    //     LOG_INFO("trigger timer event,count=%d",i++);
    // });
    // eventLoop->addTimerEvent(timer_event);
    // eventLoop->loop();
    return 0;
}