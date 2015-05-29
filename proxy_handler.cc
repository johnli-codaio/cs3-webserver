#include "proxy_handler.h"
#include <string>
#include <vector>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <sstream>

#define MAX_LENGTH 1024

/*
 * Configure will set the values for url and port in the Proxy Handler.
 */
void ProxyHandler::Configure(const NginxConfig& child_config_block) {
    /* First, we retrieve the host port number, and the host url */
    /* The format of the block should be: host <url> <port> */
    std::vector<std::shared_ptr<NginxConfigStatement>>::const_iterator it;
    for (it = child_config_block.statements_.begin();
         it != child_config_block.statements_.end();
         ++it) {

        if ((*it)->tokens_.size() > 2) {
            if ((*it)->tokens_[0] == "host") {
                this->url = (*it)->tokens_[1];
                this->port = std::stoi((*it)->tokens_[2]);
            }
        }
    }
}

/*
 * This function will handle the request of Proxy Handler 
 * A lot of this code taken from Justin Leong.
 */
std::string ProxyHandler::HandleRequest(const HTTPRequest& req) {

    /* Setting up the ASIO synchronous socket */
    boost::asio::io_service io_service;
    boost::system::error_code error;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
    boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);
    boost::asio::ip::tcp::socket sock(io_service);
    acceptor.accept(sock);

    std::string request = "";

    /* Remove the handler extension in request */
    std::istringstream iss(req.path);
    std::string handlerExtension = "";
    std::getline(iss, handlerExtension, '/');
    std::getline(iss, handlerExtension, '/');

    // Get the destination of the file
    std::string dest(req.path.begin() + handlerExtension.size() + 1, req.path.end());
    dest = "/" + dest;

    // Adding the request.
    request += req.method + " " + dest + " HTTP/1.1 \r\n\r\n";

    // Adding the headers into the request.
    for(unsigned int i = 0; i < req.headers.size(); i++) {
        request += req.headers[i].first + " " + req.headers[i].second + "\r\n";
    }

    // Adding the body to the request.
    request += "\r\n" + req.request_body;

    //Write this request into socket
    boost::asio::write(sock, boost::asio::buffer(request), error);

    // Now, we read the response.
    std::string response = "";
    for(;;) {
        char data[MAX_LENGTH];
        size_t length = sock.read_some(boost::asio::buffer(data), error);

        // Check the errors
        if(error == boost::asio::error::eof)
            break;
        else if (error)
            throw boost::system::system_error(error);

        std::string read_response(data, length);
        response += read_response;
    }
    return response;
}
