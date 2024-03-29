#include<sys/timerfd.h>
#include<unistd.h>
#include "timer.h"
#include "../common/log.h"
#include "../common/util.h"

namespace rocket{

Timer::Timer():FdEvent(){

    m_fd=timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK|TFD_CLOEXEC);
    LOG_DEBUG("timer fd=%d",m_fd);
    //fd可读事件放到eventloop上监听
    listen(FdEvent::IN_EVENT,std::bind(&Timer::onTimer,this));
}

Timer::~Timer(){
    
}

void Timer::resetArriveTime(){
    ScopedLock<Mutex>lock(m_mutex);
    auto tmp=m_pending_events;
    lock.unlock();
    if(tmp.size()==0){
        return;
    }
    int64_t now=getNowMs();
    int64_t interval=0;
    auto it=tmp.begin();
    if(it->second->getArriveTime()>now){
        interval=it->second->getArriveTime()-now;
    }else{
        interval=100;
    }

    timespec ts;
    memset(&ts,0,sizeof(ts));
    ts.tv_sec=interval/1000;
    ts.tv_nsec=(interval%1000)*1000000;

    itimerspec value;
    memset(&value,0,sizeof(value));
    value.it_value=ts;

    int rt=timerfd_settime(m_fd,0,&value,NULL);
    if(rt!=0){
        LOG_ERROR("timerfd_settime error,errno=%d,error=%s",errno,strerror(errno))
    }

    LOG_DEBUG("timer reset to %lld",now+interval);

}

void Timer::addTimerEvent(TimerEvent::ptr event){
    bool is_reset_timerfd=false;

    ScopedLock<Mutex> lock(m_mutex);
    if(m_pending_events.empty()){
        is_reset_timerfd=true;
    }else{
        auto it=m_pending_events.begin();
        if((*it).second->getArriveTime()>event->getArriveTime()){
            is_reset_timerfd=true;
        }
    }
    m_pending_events.emplace(event->getArriveTime(),event);
    lock.unlock();
    if(is_reset_timerfd){
        resetArriveTime();
    }
}

void Timer::deleteTimerEvent(TimerEvent::ptr event){
    event->setCancel(true);
    ScopedLock<Mutex>lock(m_mutex);
    //查找第一个和最后一个小于event->getArriveTime()的元素位置，即触发的所有定时器
    auto begin=m_pending_events.lower_bound(event->getArriveTime());
    auto end=m_pending_events.upper_bound(event->getArriveTime());

    auto it=begin;
    for(it=begin;it!=end;it++){
        if(it->second==event){
            break;
        }
    }
    //如果触发的定时器中有要删除的事件，那就在任务队列中删除
    if(it!=end){
        m_pending_events.erase(it);
    }
    lock.unlock();
    LOG_DEBUG("success delete TimerEvent at arrive time %lld",event->getArriveTime())
}

void Timer::onTimer(){
    //处理缓冲区数据，防止下一次继续触发可读时间
    char buf[8];
    while(1) {
        if ((read(m_fd, buf, 8) == -1) && errno == EAGAIN) {
            break;
        }
    }

    //执行定时任务
    int64_t now=getNowMs();

    std::vector<TimerEvent::ptr>tmps;
    std::vector<std::pair<int64_t,std::function<void()>>>tasks;
    ScopedLock<Mutex>lock(m_mutex);
    auto it=m_pending_events.begin();
    for(it=m_pending_events.begin();it!=m_pending_events.end();++it){
        if((*it).first<=now){
            if(!(*it).second->isCanceled()){
                tmps.push_back((*it).second);
                tasks.push_back(std::make_pair(it->second->getArriveTime(),it->second->getCallBack()));
            }
        }else{
            break;
        }
    }
    m_pending_events.erase(m_pending_events.begin(),it);
    lock.unlock();

    //把重复的Event再次添加
    for(auto it=tmps.begin();it!=tmps.end();++it){
        if((*it)->isReapeted()){
            (*it)->resetArriveTime();
            addTimerEvent(*it);
        }
    }
    resetArriveTime();

    for(auto i:tasks){
        if(i.second){
            i.second();
        }
    }
}

}