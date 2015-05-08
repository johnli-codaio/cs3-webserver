#ifndef _CONFIGMANAGER_H_INCLUDED
#define _CONFIGMANAGER_H_INCLUDED

#include "config_parser.h"

class ConfigManager {
    NginxConfig config;
    
    public:
    ConfigManager(NginxConfig);
    ConfigManager(const char*);    
    int getPort() {return getPort(config);};
    std::string getBaseDirectory(NginxConfig& config);
    
    private:
    int getPort(NginxConfig&);
};

#endif
