#ifndef _CONFIGMANAGER_H_INCLUDED
#define _CONFIGMANAGER_H_INCLUDED

#include "config_parser.h"
#include <list>

class ConfigManager {
    NginxConfig config;
    
    public:
    ConfigManager(NginxConfig);
    ConfigManager(const char*);    
    int getPort() {return getPort(config);};
    
    
    private:
    int getPort(NginxConfig&);
    // get the config statement for each handler type, all collected into a list
    std::list<NginxConfig*> getConfigs(const NginxConfig& config);
    // get the static path given a NginxConfig with a childblock containing
    // root binding.
    static std::string getPath(const NginxConfig& config);
};

#endif
