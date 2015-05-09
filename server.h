#ifndef _SERVER_H_INCLUDED
#define _SERVER_H_INCLUDED

#include <boost/asio.hpp>
#include <string>
#include "config_parser.h"

using boost::asio::ip::tcp;

/*
 * This server class is a pure virtual base class that will be used
 * in order to set up the general behavior that will be implemented
 * in inheriting classes.
 */
class server {
public:
	// Constructor
	server(int port, int server_type);
	// Destructor
	~server();

	// General functions to run the server
	void session(tcp::socket sock, std::string request);
	void run(boost::asio::io_service& io_service);
	void call();
	
	// Specific handler types

	// Hello world handler
	void hello_world();

	// Echo handler
	void echo(tcp::socket sock);

	// Request handler
	void request_handler(tcp::socket sock);

	// Helper functions for request_handler
	std::string getResponse(std::string request);
	bool in_dir (const std::string& name);

private:
	// port number
	int port;

	// server_types: 1 - hello world, 2 - echo, 3 - response
	int server_type;
};

const int max_length = 1024;
const std::string message = "<html><body>Hello, world!</body></html>";

#endif 
