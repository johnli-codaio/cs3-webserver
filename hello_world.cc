// Based on code from Synchronous TCP Daytime Server
// at http://www.boost.org/doc/libs/1_57_0/doc/html/boost_asio/tutorial/tutdaytime2.html

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "server.h"

using boost::asio::ip::tcp;

const std::string message = "<html><body>Hello, world!</body></html>";

void run(int port) {
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
    
}
