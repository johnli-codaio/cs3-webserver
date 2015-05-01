#include "config_parser.h"

class ConfigManager {
    NginxConfig config;
    
    public:
    ConfigManager(NginxConfig);
    ConfigManager(const char*);    
    int getPort() {return getPort(config);};
    
    private:
    int getPort(NginxConfig&);
};
