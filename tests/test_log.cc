#include "rocket/common/log.h"
#include"rocket/common/config.h"
#include<unistd.h>
#include<iostream>
#include<pthread.h>


void* fun(void*){
    int i=20;
    while(i--){
        LOG_DEBUG("test debug log %s","11");
        LOG_INFO("test info log %s","11");
    }
    return NULL;
}

int main(int argc,char** argv){
    rocket::Config::setGlobalConfig("conf/rocket.xml");
    rocket::Logger::InitGlobalLogger();
    pthread_t thread;
    pthread_create(&thread,NULL,&fun,NULL);
    int i=20;
    while(i--){
        LOG_DEBUG("test debug log %s","11");
        LOG_INFO("test info log %s","11");
    }

    pthread_join(thread,NULL);
    return 0;
}