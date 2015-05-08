#include "server.h"
#include "request_handler.hpp"
#include "request.hpp"
#include "reply.hpp"
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <string>

using boost::asio::ip::tcp;

// Constructor
server::server(int port, int server_type) {
	this->port = port;
	this->server_type = server_type;
}

// Destructor
server::~server() {

}

/*
 * This function takes a socket and handler type as input, then it calls the
 * appropriate handler to deal with all incoming requests.
 */
void server::session(tcp::socket sock) {
  switch (server_type) {
  	case 1:
  		hello_world();
  		break;
  	case 2:
  		echo(std::move(sock));
  		break;
  	case 3:
      request_handler();
  		break;
  	default:
  		std::cerr << "There is no server of this type.\n";
  }
}

/*
 * This function takes an io_service object as input and runs the server.
 */
void server::run(boost::asio::io_service& io_service) {
  tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
  while (true) {
    tcp::socket sock(io_service);
    a.accept(sock);
    session(std::move(sock));
  }
}

/*
 * This function calls the server object and runs it if possible.
 */
void server::call() {
  try {
    boost::asio::io_service io_service;

    run(io_service);
  }
  catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}

void server::hello_world() {
    try {
        boost::asio::io_service io_service2;
    
        tcp::acceptor acceptor(io_service2, tcp::endpoint(tcp::v4(), port));
    
        while (true) {
          tcp::socket socket(io_service2);
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

void server::echo(tcp::socket sock){
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

void server::request_handler() {
  std::string dir = "~/cs3/cs3-webserver";
  http::server::request_handler chad(dir);

  http::server::request req;
  req.uri = "localhost:35001/~/cs3/cs3-webserver/wayne.jpg";
  http::server::reply rep;

  chad.handle_request(req, rep);
  /*
   * TODO:
   * declare reuqest object
   * declare reply object
   * call handle_request()
   */
}