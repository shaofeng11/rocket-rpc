#include "timer_event.h"
#include "../common/util.h"
#include "../common/log.h"
namespace rocket{
TimerEvent::TimerEvent(int64_t interval,bool is_reapeated,std::function<void()>cb):
                    m_interval(interval),
                    m_reapeated(is_reapeated),
                    m_task(cb){
    resetArriveTime();
}

void TimerEvent::resetArriveTime(){
     m_arriveTime=getNowMs()+m_interval;
     m_isCancled=false;
     LOG_DEBUG("success create timer event,will excute at [%lld]",m_arriveTime);
}
}