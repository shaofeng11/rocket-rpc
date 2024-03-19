#include<assert.h>
#include "io_thread.h"
#include "../common/log.h"
#include "../common/util.h"
namespace rocket{

IOThread::IOThread(){
    int rt=sem_init(&m_init_semaphore,0,0);
    assert(rt==0);

    rt = sem_init(&m_start_semaphore, 0, 0);
    assert(rt == 0);

    pthread_create(&m_thread,nullptr,&IOThread::Main,this);
    
    sem_wait(&m_init_semaphore);
    LOG_DEBUG("IOThread [%d] create success",m_threadId);
}
IOThread::~IOThread(){
    m_eventLoop->stop();
    sem_destroy(&m_init_semaphore);
    sem_destroy(&m_start_semaphore);
    pthread_join(m_thread,NULL);

    if(m_eventLoop){
        delete m_eventLoop;
        m_eventLoop=NULL;
    }
}
void* IOThread::Main(void* arg){
    IOThread* thread=static_cast<IOThread*>(arg);
    thread->m_eventLoop=new EventLoop();
    thread->m_threadId=getThreadId();

    sem_post(&thread->m_init_semaphore);
    
    LOG_DEBUG("IOThread %d created, wait start semaphore", thread->m_threadId);

    //先不开启循环，等待条件变量释放
    sem_wait(&thread->m_start_semaphore);
    LOG_DEBUG("IOThread %d start loop ", thread->m_threadId);
    thread->m_eventLoop->loop();

    LOG_DEBUG("IOThread %d end loop ", thread->m_threadId);

    return NULL;
}

void IOThread::start(){
  LOG_DEBUG("Now invoke IOThread %d", m_threadId);
  sem_post(&m_start_semaphore);
}
void IOThread::join(){
    pthread_join(m_thread,NULL);
}
}