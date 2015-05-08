#include "ConfigManager.h"
#include "server.h"


/*
 * This main function is used to ask the user for a config file
 * path and get the port number from the config file.  Then, it
 * runs the server on the desired port.
 */

int main(int argc, char* argv[]) {
	// Check that the user specified the proper number of arguments.
    if (argc != 2) {
        printf("Usage: ./webserver <path to config file>\n");
        return 0;
    }
    
    // Make a config object and get the port number from the config file.
    ConfigManager config((const char*)argv[1]);
    int port = config.getPort();
    
    // Run the server.
    run(port);
    
    return 0;
}
