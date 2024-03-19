#ifndef ROCKET_NET_TIMER_H
#define ROCKET_NET_TIMER_H
#include<map>
#include"timer_event.h"
#include"fd_event.h"
#include"../common/mutex.h"
namespace rocket{

class Timer : public FdEvent {
public:

  Timer();

  ~Timer();

  void addTimerEvent(TimerEvent::ptr event);

  void deleteTimerEvent(TimerEvent::ptr event);

  void onTimer(); // 当发生了 IO 事件后，eventloop 会执行这个回调函数

 private:
  void resetArriveTime();
 private:
  std::multimap<int64_t, TimerEvent::ptr> m_pending_events;
  Mutex m_mutex;

};
}

#endif