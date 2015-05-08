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
	server(int port, int server_type);
	~server();
	void session(tcp::socket sock);
	void run(boost::asio::io_service& io_service);
	void call();
	void hello_world();
	void echo(tcp::socket sock);
	void request_handler();

private:
	// port number
	int port;

	// server_types: 1 - hello world, 2 - echo, 3 - response
	int server_type;
};

const int max_length = 1024;
const std::string message = "<html><body>Hello, world!</body></html>";

#endif 
