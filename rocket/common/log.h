#ifndef ROCKET_LOG_H__
#define ROCKET_LOG_H__
#include<stdint.h>
#include<string>
#include<memory>
#include<queue>
#include<vector>
#include"config.h"
#include"mutex.h"



namespace rocket{

enum LogLevel{
    UNKNOW=0,
    DEBUG=1,
    INFO=2,
    ERROR
};



template<typename... Args>
std::string formatString(const char* str,Args&&... args){
    int size=snprintf(nullptr,0,str,args...);
    std::string result;
    if(size>0){
        result.resize(size);
        snprintf(&result[0],size+1,str,args...);
    }

    return result;
}

#define LOG_DEBUG(str,...) \
    if(rocket::Logger::getGlobalLogger()->getLogLevel()<=rocket::LogLevel::DEBUG){ \
        rocket::Logger::getGlobalLogger()->pushLog(rocket::LogEvent(rocket::LogLevel::DEBUG).toString() \
            +"["+std::string(__FILE__)+":"+std::to_string(__LINE__)+"]\t"+rocket::formatString(str,##__VA_ARGS__)+"\n"); \
        rocket::Logger::getGlobalLogger()->log(); \
    } \

#define LOG_INFO(str,...) \
    if(rocket::Logger::getGlobalLogger()->getLogLevel()<=rocket::INFO){ \
        rocket::Logger::getGlobalLogger()->pushLog(rocket::LogEvent(rocket::LogLevel::INFO).toString() \
            +"["+std::string(__FILE__)+":"+std::to_string(__LINE__)+"]\t"+rocket::formatString(str,##__VA_ARGS__)+"\n"); \
        rocket::Logger::getGlobalLogger()->log(); \
    } \

#define LOG_ERROR(str,...) \
    if(rocket::Logger::getGlobalLogger()->getLogLevel()<=rocket::ERROR){ \
        rocket::Logger::getGlobalLogger()->pushLog(rocket::LogEvent(rocket::LogLevel::ERROR).toString() \
            +"["+std::string(__FILE__)+":"+std::to_string(__LINE__)+"]\t"+rocket::formatString(str,##__VA_ARGS__)+"\n"); \
        rocket::Logger::getGlobalLogger()->log(); \
    } \

class AsyncLogger{
public:
    typedef std::shared_ptr<AsyncLogger>ptr;
    //AsyncLogger(const std::)
private:
    std::queue<std::vector<std::string>> m_buffer;
    std::string m_fileName;
    std::string m_filePath;
    int m_maxFilesize=0;
};


class LogEvent{
public:
    LogEvent(LogLevel level):m_level(level){}

    std::string toString();

    std::string getFileName() const{ return m_name;}
    LogLevel getLevel() const { return m_level;}
private:
    std::string m_name;
    int32_t m_line;
    int32_t m_pid;
    int32_t m_tid;
    LogLevel m_level;
};



LogLevel stringToLogLevel(const std::string&log_level);
std::string LogLevelToString(const LogLevel& level);

class Logger{
public:
    typedef std::shared_ptr<Logger>ptr;
    typedef Mutex MutexType;

    Logger(LogLevel level):m_level(level){};

    void log();
    void pushLog(const std::string& msg);
    static void InitGlobalLogger();
    static Logger* getGlobalLogger();

    LogLevel getLogLevel() const {return m_level;}
private:
    LogLevel m_level;

    //需要打印的日志
    std::queue<std::string>m_buffer;
    MutexType m_mutex;

};
}

#endif