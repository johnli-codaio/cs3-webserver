// Some of the functions below are modelled on methods used by Megan Keehan
// and Eric Gorlin.

#include "server.h"
#include "config_parser.h"
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <string>
#include <sys/stat.h>
#include <fstream>

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
void server::session(tcp::socket sock, std::string request) {
  switch (server_type) {
  	case 1:
  		hello_world();
  		break;
  	case 2:
  		echo(std::move(sock));
  		break;
  	case 3:
      request_handler(std::move(sock));
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
    session(std::move(sock), "/chad.txt");
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

// This functions handles the hello world server.
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

// This function handles the echo server.
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

// This function handles the request handling server.
void server::request_handler(tcp::socket sock) {
  std::string response;
  response = getResponse("/chad.txt");
  boost::asio::write(sock, boost::asio::buffer(response));
}

// This function takes a response string and returns a string representing
// the contents of the file requested, or a 404 error if the file does
// not exist.  Modelled on method used by Megan Keehan and Eric Gorlin.
std::string server::getResponse(std::string request) {
  std::string static_path = "/home/connorjcrowley/cs3/cs3-webserver";
  std::string requested_file;

  if (in_dir(static_path + request)) {
        std::ifstream file(static_path + request);
        std::string buffer;
        while (std::getline(file, buffer)) {
          requested_file += buffer;
          requested_file.push_back('\n');
        }
  }
  else {
    std::string err_str = "error 404 page not found";
    return err_str;
  }
  return requested_file;
}

// This function detrmines whether a file is in the directory, taking a
// filename as input by reference and returning a boolean.
// Found on http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
bool server::in_dir (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}