#include"config.h"
#include<iostream>
#include<tinyxml/tinyxml.h>

#define READ_XML_NODE(name,parent) \
TiXmlElement* name##_node=parent->FirstChildElement(#name); \
if(!name##_node){ \
    printf("Start rocket server error,fail to read node [%s]\n",#name); \
    exit(0); \
} \

#define READ_STR_FROM_XML_NODE(name,parent) \
TiXmlElement* name##_node=parent->FirstChildElement(#name); \
if(!name##_node ||!name##_node->GetText()){ \
    printf("Start rocket server error,fail to read config file %s\n",#name); \
    exit(0); \
} \
std::string name##_str=std::string(name##_node->GetText()); \

namespace rocket{

static Config* g_config=NULL;

Config::Config(const char* xmlfile){
    m_xml_document= new TiXmlDocument();
    bool rt=m_xml_document->LoadFile(xmlfile);
    if(!rt){
        printf("Start rocket server error,failed to read config file %s,errorinfo[%s] \n",
        xmlfile,m_xml_document->ErrorDesc());
        exit(0);
    }
    READ_XML_NODE(root,m_xml_document);
    READ_XML_NODE(log,root_node);
    //READ_XML_NODE(server, root_node);
    READ_STR_FROM_XML_NODE(log_level,log_node);
}

Config::Config(){
    m_logLevel="DEBUG";
}

Config::~Config(){
    if (m_xml_document) {
        delete m_xml_document;
        m_xml_document = NULL;
  }
}

Config* Config::getGlobalConfig(){
    return g_config;
}
void Config::setGlobalConfig(const char* xmlfile){
    if(g_config==NULL){
        if(xmlfile!=NULL){
            g_config=new Config(xmlfile);
        }else{
            g_config=new Config();
        }
    }
}
}