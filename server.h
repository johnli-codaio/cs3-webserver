#ifndef _SERVER_H_INCLUDED
#define _SERVER_H_INCLUDED

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

/*
 * This server class is a pure virtual base class that will be used
 * in order to set up the general behavior that will be implemented
 * in inheriting classes.
 */
class server {
public:
	server(int port);
	~server();
	void session(tcp::socket sock);
	void run(boost::asio::io_service& io_service);
	void run2();

private:
	// port number
	int port;
};

const int max_length = 1024;

#endif 
