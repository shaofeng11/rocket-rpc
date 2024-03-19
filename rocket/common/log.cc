#include <sys/time.h>
#include <time.h>
#include<sstream>
#include"log.h"
#include"util.h"
namespace rocket{

static Logger* g_logger=NULL;


LogLevel stringToLogLevel(const std::string& log_level){
    if(log_level=="DEBUG"){
        return DEBUG;
    }else if(log_level=="INFO"){
        return INFO;
    }else if(log_level=="ERROR"){
        return ERROR;
    }else{
        return UNKNOW;
    }
}
std::string LogLevelToString(const LogLevel& level){
    switch (level){
    case DEBUG:
        return "DEBUG";
    case INFO:
        return "INFO";
    case ERROR:
        return "ERROR";
    default:
        return "UNKNOW";
    }
}

std::string LogEvent::toString(){
    struct timeval now_time;
    gettimeofday(&now_time,nullptr);

    struct tm now_time_t;
    localtime_r(&now_time.tv_sec,&now_time_t);
    char buf[128];
    strftime(&buf[0],sizeof(buf),"%y-%m-%d %H:%M:%S",&now_time_t);
    std::string time_str(buf);
    int ms=now_time.tv_usec/1000;
    time_str=time_str+"."+std::to_string(ms);

    m_pid=getPid();
    m_tid=getThreadId();

    std::stringstream ss;
    ss<<"["<<LogLevelToString(m_level)<<"]\t"
        <<"["<<time_str<<"]\t"
        <<"["<<m_pid<<":"<<m_tid<<"]\t";
    return ss.str();
}

void Logger::log(){
    ScopedLock<Mutex> lock(m_mutex);
    std::queue<std::string>tmp;
    m_buffer.swap(tmp);

    lock.unlock();
    while(!tmp.empty()){
        std::string msg=tmp.front();
        tmp.pop();
        printf(msg.c_str());
    }
}   
void Logger::pushLog(const std::string& msg){
    MutexType::Lock lock(m_mutex);
     //MutexType::Lock lock(m_mutex);
    m_buffer.push(msg);
    lock.unlock();
}

void Logger::InitGlobalLogger(){
    LogLevel global_log_level=stringToLogLevel(Config::getGlobalConfig()->m_logLevel);
    printf("Init log level [%s]\n",LogLevelToString(global_log_level).c_str());
    g_logger=new Logger(global_log_level);
    //g_logger->init();
}

Logger* Logger::getGlobalLogger(){
    return g_logger;
}
}