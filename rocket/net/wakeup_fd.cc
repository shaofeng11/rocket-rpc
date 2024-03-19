#include <unistd.h>
#include "wakeup_fd.h"
#include"../common/log.h"
namespace rocket{

WakeUpEvent::WakeUpEvent(int fd):FdEvent(fd){

}
WakeUpEvent::~WakeUpEvent(){

}
//当调用wakeup方法时，向wake_fd写入一个'a'，替换pipe，pipe需要两个fd，eventfd需要1个
void WakeUpEvent::wakeup(){
    
    char buf[8]={'a'};
    int rt=write(m_fd,buf,8);
    if(rt!=8){
        LOG_ERROR("write to wakeup fd less than 8 bytes,fd [%d]",m_fd);
    }
}
}

