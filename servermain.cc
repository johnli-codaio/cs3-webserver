#include "server.h"
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: blocking_tcp_echo_server <port> <server_type>\n";
      std::cerr << "server_types: 1 - hello world, 2 - echo, 3 - response\n";
      return 1;
    }

    server *serv = new server(std::atoi(argv[1]), std::atoi(argv[2]));

    serv->call();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
