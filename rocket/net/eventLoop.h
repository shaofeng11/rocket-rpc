#ifndef ROCKET_NET_EVENTLOOP_H__
#define ROCKET_NET_EVENTLOOP_H__
#include<pthread.h>
#include<sys/eventfd.h>
#include<set>
#include<functional>
#include<queue>
#include "fd_event.h"
#include"../common/mutex.h"
#include"wakeup_fd.h"
#include"timer.h"
namespace rocket{

class EventLoop{
public:
    EventLoop();
    ~EventLoop();
    void loop();
    void wakeup();
    void stop();
    
    //加到树上的Event是自己封装的结构体
    void addEpollEvent(FdEvent* event);
    void delEpollEvent(FdEvent* event);

    bool isInLoopThread();

    bool isLooping() const{return m_is_looping;}
    
    void addTask(std::function<void()>cb,bool is_wakeUp=false);

    void addTimerEvent(TimerEvent::ptr event);


public:
    static EventLoop* getCurrentEventLoop();
private:
    void dealWakeup();
    void initWakeUpFdEvent();
    void initTimer();

    
private:
    pid_t m_thread_id=0;
    int m_epfd=0;
    //wakeup fd，唤醒fd
    int m_wakeup_fd=0;

    //唤醒事件
    WakeUpEvent* m_wakeup_fd_event=nullptr;
    bool m_stop_flag=false;

    //epoll_wait正在监听的fd
    std::set<int>m_listen_fds;
    Mutex m_mutex;
    std::queue<std::function<void()>> m_pending_tasks;

    Timer* m_timer=NULL;

    bool m_is_looping{false};
};

}

#endif