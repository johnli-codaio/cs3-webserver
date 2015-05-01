#include "ConfigManager.h"
#include "server.h"


int main(int argc, char* argv[]) {
    if (argc != 2) {
    printf("Usage: ./webserver <path to config file>\n");
    return 0;
    }
    
    ConfigManager config((const char*)argv[1]);
    int port = config.getPort();
    
    run(port);
    
    return 0;
}
