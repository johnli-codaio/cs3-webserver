// Based on code from Synchronous TCP Daytime Server
// at http://www.boost.org/doc/libs/1_57_0/doc/html/boost_asio/tutorial/tutdaytime2.html

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_hello_world() {
  using namespace std; // For time_t, time and ctime;
  string ret = "<html><body>Hello, world!</body></html>";
  return ret;
}

int main() {
  try {
    boost::asio::io_service io_service;
    
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 35000));
    
    while (true) {
      tcp::socket socket(io_service);
      acceptor.accept(socket);
      std::string message = make_hello_world();

      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
  }
  
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
