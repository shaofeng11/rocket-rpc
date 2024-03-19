#ifndef ROCKET_NTE_FDEVENT_H__
#define ROCKET_NTE_FDEVENT_H__
#include<functional>
#include<sys/epoll.h>

namespace rocket{

class FdEvent{
public:
    enum TriggerEvent{
        IN_EVENT=EPOLLIN,
        OUT_EVENT=EPOLLOUT,
        ERROR_EVENT=EPOLLERR
    };

    FdEvent(int fd);

    FdEvent();
    ~FdEvent();

    void setNonBlock();

    std::function<void()> handle(TriggerEvent event);

    //给fd添加事件与回调函数
    void listen(TriggerEvent event,std::function<void()>cb,std::function<void()>error_cb=nullptr);

    int getFd() const{ return m_fd;}

    epoll_event getEpollEvent() const{ return m_listen_events;}

    void cancel(TriggerEvent event);



protected:
    int m_fd=-1;
    epoll_event m_listen_events;
    std::function<void()>m_read_cb{nullptr};
    std::function<void()>m_write_cb{nullptr};
    std::function<void()>m_error_cb{nullptr};
};

}

#endif