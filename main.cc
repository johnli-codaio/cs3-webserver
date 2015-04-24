// Based on code from Synchronous TCP Daytime Server
// at http://www.boost.org/doc/libs/1_57_0/doc/html/boost_asio/tutorial/tutdaytime2.html

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "config_parser.h"

using boost::asio::ip::tcp;

const std::string message = "<html><body>Hello, world!</body></html>";

// basically a dfs tree search
int getPort(NginxConfig config) {
    int port = -1;
    for (const auto& statement : config.statements_){
        bool listen = false;
        for (std::string token : statement->tokens_){
            if (listen){
                int port = std::stoi(token);
                return port;
            }
            else if (token == "listen"){
                listen = true;
            }
        }
        if ((statement->child_block_).get() != nullptr) {
            port = getPort(*(statement->child_block_));
        }
        if (port > 0) {
            return port;
        }
    }
    return port;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
    printf("Usage: ./config_parser <path to config file>\n");
    return 1;
    }
    NginxConfigParser config_parser;
    NginxConfig config;
    config_parser.Parse(argv[1], &config);
    int port = getPort(config);
    std::cout << "Port: " << port << '\n';
    try {
        boost::asio::io_service io_service;
    
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));
    
        while (true) {
          tcp::socket socket(io_service);
          acceptor.accept(socket);
          boost::system::error_code ignored_error;
          boost::asio::write(socket, boost::asio::buffer(message), 
            ignored_error);
        }
    }
  
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
