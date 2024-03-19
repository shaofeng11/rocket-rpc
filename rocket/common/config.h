#ifndef ROCKET_CONFIG_H__
#define ROCKET_CONFIG_H__
#include<string>
#include<map>
#include<tinyxml/tinyxml.h>
#include"log.h"
namespace rocket{

// struct RpcStub {
//   std::string name;
//   NetAddr::s_ptr addr;
//   int timeout {2000};
// };

class Config{
public:
    Config(const char* xmlfile);
    Config();
    ~Config();
    static Config* getGlobalConfig();
    static void setGlobalConfig(const char* xmlfile);
public:
    std::string m_logLevel;
    // std::string m_logFileName;
    // std::string m_logFilePath;
    // int m_logFileSize=0;
    // int m_logSyncIinteval=0;

    // int m_port=0;
    // int m_ioThreads=0;

    TiXmlDocument* m_xml_document{NULL};

    //std::map<std::string,RpcStub> m_rpc_stubs;
};

}

#endif