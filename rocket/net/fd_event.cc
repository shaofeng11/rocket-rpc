#include<string.h>
#include<fcntl.h>
#include "fd_event.h"
#include "../common/log.h"
namespace rocket{
FdEvent::FdEvent(int fd):m_fd(fd){
    memset(&m_listen_events,0,sizeof(m_listen_events));
}

FdEvent::FdEvent(){
    memset(&m_listen_events,0,sizeof(m_listen_events));
}

FdEvent::~FdEvent(){

}

std::function<void()> FdEvent::handle(TriggerEvent event){
    std::function<void()>cb;
    if(event==IN_EVENT){
        cb=m_read_cb;
    }else if(event==OUT_EVENT){
        cb=m_write_cb;
    }else{
        cb=m_error_cb;
    }
    return cb;
}

void FdEvent::listen(TriggerEvent event,std::function<void()>cb,std::function<void()>error_callback){
    if(event==IN_EVENT){
        m_listen_events.events|=EPOLLIN;
        m_read_cb=cb;
    }else{
        m_listen_events.events|=EPOLLOUT;
        m_write_cb=cb;
    }
    if(m_error_cb==nullptr){
        m_error_cb=cb;
    }else{
        m_error_cb=nullptr;
    }
    m_listen_events.data.ptr=this;
}


void FdEvent::cancel(TriggerEvent event){
    if(event==IN_EVENT){
        m_listen_events.events&=(~EPOLLIN);
    }else{
        m_listen_events.events&=(~EPOLLOUT);
    }
}

void FdEvent::setNonBlock(){
    int flag=fcntl(m_fd,F_GETFL,0);
    if(flag & O_NONBLOCK){
        return;
    }

    fcntl(m_fd,F_SETFL,flag|O_NONBLOCK);
}

}
