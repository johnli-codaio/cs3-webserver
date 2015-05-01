#include "client.h"
#include "ConfigManager.h"
#include "server.h"
#include <string.h>
#include <thread>

int main (int argc, char* argv[]){
    if (argc != 3) {
        printf("Usage: ./webserver <path to config file> <message>\n");
        return 0;
    }
    ConfigManager config((const char*)argv[1]);
    int port = config.getPort();
    std::thread t(run, port);
    std::cout << "server running ..... \n";
    
    char* reply = send("localhost", (std::to_string(port)).c_str(), argv[2]);
    
    std::cout<< "The reply is: " << reply << "\n";
    if (strcmp(argv[2], reply) == 0)
        std::cout << "MATCH\n";
    else
        std::cout << "NO MATCH\n";
    t.join();
    return 0;
}
