#ifndef _PROXY_HANDLER_H_
#define _PROXY_HANDLER_H_

#include "request_handler.h"
#include "ConfigManager.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <fstream>

class ProxyHandler : public RequestHandler {
  public:
    void Configure(const NginxConfig& child_config_block);
    std::string HandleRequest(const HTTPRequest& req);
  private:
    std::string url;
    int port;
};

#endif // _PROXY_HANDLER_H_