#include "eventLoop.h"
#include "../common/log.h"
#include "../common/util.h"
#include<unistd.h>
#include<sys/socket.h>
#include<sys/epoll.h>

#define ADD_TO_EPOLL() \
        auto it=m_listen_fds.find(event->getFd()); \
        int op=EPOLL_CTL_ADD; \
        if(it!=m_listen_fds.end()){ \
            op=EPOLL_CTL_MOD; \
        } \
        epoll_event tmp=event->getEpollEvent(); \
        LOG_INFO("epoll_event.events = %d", (int)tmp.events); \
        int rt=epoll_ctl(m_epfd,op,event->getFd(),&tmp); \
        if(rt==-1){ \
            LOG_ERROR("failed epoll_ctl when add fd %d,errno=%d,error info=%s" \
                        ,event->getFd(),errno,strerror(errno)); \
        } \
        m_listen_fds.insert(event->getFd()); \
        LOG_DEBUG("add event success fd[%d]",event->getFd()) \

#define DEL_TO_EPOLL() \
        auto it=m_listen_fds.find(event->getFd()); \
        if(it==m_listen_fds.end()){ \
            return; \
        } \
        int op=EPOLL_CTL_DEL; \
        epoll_event tmp=event->getEpollEvent(); \
        LOG_INFO("epoll_event.events = %d", (int)tmp.events); \
        int rt=epoll_ctl(m_epfd,op,event->getFd(),&tmp); \
        if(rt==-1){ \
            LOG_ERROR("failed epoll_ctl when DEL fd %d,errno=%d,error info=%s" \
                        ,event->getFd(),errno,strerror(errno)); \
        } \
        m_listen_fds.erase(event->getFd()); \
        LOG_DEBUG("del event success fd[%d]",event->getFd()) \

namespace rocket{

//一个线程有一个eventloop
static thread_local EventLoop* t_current_eventloop=NULL;
static int g_epoll_timeout=10000;
static int g_epoll_max_events=10;
EventLoop::EventLoop(){
    if(t_current_eventloop){
        LOG_ERROR("failed to create event loop,thread thread has created eventloop");
        exit(0);
    }
    m_thread_id=getThreadId();

    m_epfd=epoll_create(10);
    if(m_epfd==-1){
        LOG_ERROR("failed to create event loop,epoll create error,error info[%d]",errno);
        exit(0);
    }

    initWakeUpFdEvent();
    initTimer();
   
    
    LOG_INFO("success create eventloop in thread %d",m_thread_id);
    t_current_eventloop=this;
}

EventLoop::~EventLoop(){
    close(m_epfd);
    if(m_wakeup_fd_event){
        delete m_wakeup_fd_event;
        m_wakeup_fd_event=NULL;
    }
    if(m_timer){
        delete m_timer;
        m_timer=NULL;
    }
}

void EventLoop::initTimer(){
    m_timer=new Timer();
    //将定时器添加到监听树上
    addEpollEvent(m_timer);
}

void EventLoop::initWakeUpFdEvent(){
    //eventfd()函数会创建一个“eventfd”对象，用户空间的应用程序可以用这个eventfd来实现事件的等待或通知机制，
    //也可以用于内核通知新的事件到用户空间应用程序。
    //这个对象包含一个64-bit的整形计数器，内核空间维护这个计数器，创建这个计数器的时候使用第一个入参initval来初始化计数器。
    m_wakeup_fd=eventfd(0,EFD_NONBLOCK);
    if(m_wakeup_fd<0){
        LOG_ERROR("failed to create event loop,eventfd create error,error info[%d]",errno);
        exit(0);
    }

    m_wakeup_fd_event=new WakeUpEvent(m_wakeup_fd);
    m_wakeup_fd_event->listen(FdEvent::IN_EVENT,[this](){
        char buf[8];
        while(read(m_wakeup_fd,buf,8)!=-1 && errno!=EAGAIN){
        }
        LOG_DEBUG("read full bytes from wakeup fd[%d]",m_wakeup_fd);
    });

    addEpollEvent(m_wakeup_fd_event);
}

void EventLoop::loop(){
    m_is_looping=true;
    //m_stop_flag=false
    while(!m_stop_flag){
        ScopedLock<Mutex> lock(m_mutex);
        std::queue<std::function<void()>>tmp_tasks;
        tmp_tasks.swap(m_pending_tasks);
        lock.unlock();

        //如果任务队列有任务，则先执行任务(任务一般都是向监听红黑树上添加或删除事件，也有可能是写数据)，再开始epoll_wait
        while(!tmp_tasks.empty()){
            std::function<void()>cb=tmp_tasks.front();
            tmp_tasks.pop();
            if(cb){
                cb();
            }
        }
        epoll_event result_events[g_epoll_max_events];
        LOG_DEBUG("now begin to epoll wait");
        int rt=epoll_wait(m_epfd,result_events,g_epoll_max_events,g_epoll_timeout);
        LOG_DEBUG("now end to epoll wait,rt=%d",rt);
        if(rt<0){
            LOG_ERROR("epoll_wait error,errno=%d,error=%s",errno,strerror(errno));
        }else{
            for(int i=0;i<rt;i++){
                epoll_event trigger_event=result_events[i]; 

                FdEvent* fd_event=static_cast<FdEvent*>(trigger_event.data.ptr);
                if(fd_event==NULL){
                    continue;
                }
                if(trigger_event.events&EPOLLIN){
                    LOG_DEBUG("fd %d trigger EPOLLIN event",fd_event->getFd());
                    addTask(fd_event->handle(FdEvent::IN_EVENT));
                }
                if(trigger_event.events &EPOLLOUT){
                    LOG_DEBUG("fd %d trigger EPOLLOUT event",fd_event->getFd());
                    addTask(fd_event->handle(FdEvent::OUT_EVENT));
                }
                if(trigger_event.events &EPOLLERR){
                    LOG_DEBUG("fd %d trigger EPOLLERROR event",fd_event->getFd());
                    if(fd_event->handle(FdEvent::ERROR_EVENT)!=nullptr){
                        addTask(fd_event->handle(FdEvent::OUT_EVENT));
                    }
                }
                }
            }
        }
    }

void EventLoop::wakeup(){
    LOG_INFO("WAKE UP");
    m_wakeup_fd_event->wakeup();
}

void EventLoop::stop(){
    m_stop_flag=true;
    wakeup();
}

void EventLoop::dealWakeup(){

}

void EventLoop::addEpollEvent(FdEvent* event){
    if(isInLoopThread()){
        ADD_TO_EPOLL();
    }else{
        auto cb=[this,event](){
            ADD_TO_EPOLL();
        };
        addTask(cb,true);
    }
    
}
void EventLoop::delEpollEvent(FdEvent* event){
    if(isInLoopThread()){
        DEL_TO_EPOLL();
    }else{
        auto cb=[this,event](){
            DEL_TO_EPOLL();
        };
        addTask(cb,true);
    }
}

bool EventLoop::isInLoopThread(){
    return getThreadId()==m_thread_id;
}

//如果线程正在loop(epoll_wait)，若需要唤醒，则向wakup_fd中写数据，这样epoll_wait就会返回
void EventLoop::addTask(std::function<void()>cb,bool is_wakeUp){
    ScopedLock<Mutex> lock(m_mutex);
    m_pending_tasks.push(cb);
    lock.unlock();
    if(is_wakeUp){
        wakeup();
    }
}

void EventLoop::addTimerEvent(TimerEvent::ptr event){
    m_timer->addTimerEvent(event);
}

EventLoop* EventLoop::getCurrentEventLoop(){
    if(t_current_eventloop){
        return t_current_eventloop;
    }
    t_current_eventloop=new EventLoop();
    return t_current_eventloop;
}

}