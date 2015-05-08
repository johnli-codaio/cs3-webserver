#include "server.h"
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>

using boost::asio::ip::tcp;

// Constructor
server::server(int port) {
	this->port = port;
}

// Destructor
server::~server() {

}

void server::session(tcp::socket sock) {
  try {
    for (;;) {
      char data[max_length];

      boost::system::error_code error;
      size_t length = sock.read_some(boost::asio::buffer(data), error);
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      boost::asio::write(sock, boost::asio::buffer(data, length));
      sock.close();
    }
  }
  catch (std::exception& e) {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
}

void server::run(boost::asio::io_service& io_service) {
  tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
  while (true) {
    tcp::socket sock(io_service);
    a.accept(sock);
    session(std::move(sock));
  }
}

void server::run2() {
  try {
    boost::asio::io_service io_service;

    run(io_service);
  }
  catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}
