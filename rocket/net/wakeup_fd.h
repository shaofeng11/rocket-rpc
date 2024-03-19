#ifndef ROCKET_WAKEUP_FD_H_
#define ROCKET_WAKEUP_FD_H_
#include "fd_event.h"
namespace rocket{
class WakeUpEvent :public FdEvent{
public:
    WakeUpEvent(int fd);
    ~WakeUpEvent();
    void wakeup();
private:

};
}

#endif