//
// blocking_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// This source code came from 
// http://www.boost.org/doc/libs/1_58_0/doc/html/boost_asio/example/cpp11/echo/blocking_tcp_echo_server.cpp

#include <cstdlib>
#include <iostream>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

const int max_length = 1024;

void session(tcp::socket sock)
{
  try
  {
    for (;;)
    {
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
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
}

void server(boost::asio::io_service& io_service, unsigned short port, bool cont)
{
  tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
  do
  {
    tcp::socket sock(io_service);
    a.accept(sock);
    session(std::move(sock));
  }while(cont);
}

void run(int port, bool cont)
{
  try
  {
    boost::asio::io_service io_service;

    server(io_service, port, cont);
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}
