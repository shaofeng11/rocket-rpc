#ifndef ROCKET_NET_IO_THREAD_H__
#define ROCKET_NET_IO_THREAD_H__
#include<pthread.h>
#include<semaphore.h>
#include "eventLoop.h"

namespace rocket{

class IOThread{
public:
    IOThread();
    ~IOThread();

    EventLoop* getEventLoop() const{return m_eventLoop;}
    void start();
    void join();
public:
    static void* Main(void* arg);
private:
    pid_t m_threadId{-1};
    pthread_t m_thread{0};
    EventLoop* m_eventLoop{NULL};//io线程的eventloop对象

    sem_t m_init_semaphore;
    sem_t m_start_semaphore;
};
}
#endif