#ifndef ROCKET_MUTEX_H__
#define ROCKET_MUTEX_H__
#include<pthread.h>

namespace rocket{

template<class T>
class ScopedLock{
public:
    ScopedLock(T& mutex):m_mutex(mutex){
        m_mutex.lock();
        m_is_lock=true;
    }
    ~ScopedLock(){
        m_mutex.unlock();
    }
    void lock(){
        if(!m_is_lock){
            m_mutex.lock();
            m_is_lock=true;
        }
    }
    void unlock(){
        if(m_is_lock){
            m_mutex.unlock();
            m_is_lock=false;
        }
    }
private:
    T& m_mutex;
    bool m_is_lock;
};


class Mutex{
public:
    typedef ScopedLock<Mutex> Lock;
    Mutex(){
        pthread_mutex_init(&m_mutex,nullptr);
    }
    ~Mutex(){
        pthread_mutex_destroy(&m_mutex);
    }

    void lock(){
        pthread_mutex_lock(&m_mutex);
    }
    void unlock(){
        pthread_mutex_unlock(&m_mutex);
    }
private:
    pthread_mutex_t m_mutex;
};

}

#endif