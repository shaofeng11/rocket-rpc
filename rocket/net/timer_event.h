#ifndef ROCKET_NET_TIMER_EVENT_H
#define ROCKET_NET_TIMER_EVENT_H

#include<stdint.h>
#include<functional>
#include<memory>
namespace rocket{

class TimerEvent{
public:
typedef std::shared_ptr<TimerEvent>ptr;
    TimerEvent(int64_t interval,bool is_reapeated,std::function<void()>cb);


    int64_t getArriveTime() const {return m_arriveTime;}
    void setCancel(bool value){ m_isCancled=value;}
    bool isCanceled() const{ return m_isCancled;}

    bool isReapeted() const {return m_reapeated;}

    std::function<void()>  getCallBack() const{return m_task;}

    void resetArriveTime();
private:
    //具体执行时间
    int64_t m_arriveTime;
    //现在的事件到执行时间还有多久
    int64_t m_interval;
    bool m_reapeated=false;
    bool m_isCancled;

    //定时任务
    std::function<void()>m_task;
};


}

#endif