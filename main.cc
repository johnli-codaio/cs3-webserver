#include "ConfigManager.h"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <unordered_map>
#include "helloworld_handler.h"
#include "e404_handler.h"
#include "echo_handler.h"
#include "static_handler.h"
#include "ConfigManager.h"
#include "http_parser.h"

using boost::asio::ip::tcp;

const int max_length = 1024;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

std::unordered_map<std::string,RequestHandler*> handlers;

void session(socket_ptr sock)
{
  try
  {
    for (;;)
    {
      char data[max_length];

      boost::system::error_code error;
      size_t length = sock->read_some(boost::asio::buffer(data), error);
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.
        
      std::string request(data, length);
      std::string binding = request.substr(0, request.find('/', 1));
      std::string response;
      if (handlers.find(binding) == handlers.end() ) {
        binding = "404";
      }
      response = handlers[binding] -> HandleRequest(parseRequest(request));

      boost::asio::write(*sock, boost::asio::buffer(response, response.size()));
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
}

void server(boost::asio::io_service& io_service, short port)
{
  tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
  for (;;)
  {
    socket_ptr sock(new tcp::socket(io_service));
    a.accept(*sock);
    boost::thread t(boost::bind(session, sock));
  }
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
    printf("Usage: ./webserver <path to config file>\n");
    return 0;
    }
    
    ConfigManager config((const char*)argv[1]);
    int port = config.getPort();
    
    std::vector<std::shared_ptr<NginxConfigStatement>> handlerConfigs = config.getConfigs();
    std::vector<std::shared_ptr<NginxConfigStatement>>::iterator it;
    handlers = std::unordered_map<std::string,RequestHandler*>();
    
    for ( it = handlerConfigs.begin(); it != handlerConfigs.end(); it++) {
      std::string type = ((*it)->tokens_)[1];
      if (type.compare("helloworld") == 0) {
        handlers[((*it)->tokens_)[2]] = new HelloWorldHandler();
      }
      else if (type.compare("echo") == 0) {
        handlers[((*it)->tokens_)[2]] = new EchoHandler();
      }
      else if (type.compare("static") == 0) {
        RequestHandler* handler = new StaticHandler();
        handler->Configure(*((*it)->child_block_));
        handlers[((*it)->tokens_)[2]] = handler;
      }
      else {
        std::cerr << "Unsupported handler type " << type << " encountered.\n";
      }
    }
    
    handlers["404"] = new E404Handler();
    
    try
    {
      boost::asio::io_service io_service;

      using namespace std; // For atoi.
      server(io_service, port);
    }
    catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << "\n";
    }
    
    return 0;
}
