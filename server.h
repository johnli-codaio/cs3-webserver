#ifndef _SERVER_H_INCLUDED
#define _SERVER_H_INCLUDED

#include <boost/asio.hpp>

/*
 * This server class is a pure virtual base class that will be used
 * in order to set up the general behavior that will be implemented
 * in inheriting classes.
 */
class server {
public:
	server(int port);
	~server();
	virtual void session(boost::asio::ip::tcp::socket sock) = 0;
	void listen();
	void run();

private:
	// port number
	int port;

	// io_service to handle all io operations
	//boost::asio::io_service io_service;

	// acceptor that is used to let the server accept requests
	//boost::asio::ip::tcp::acceptor acceptor;
};

#endif 
