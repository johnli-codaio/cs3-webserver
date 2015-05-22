#ifndef _404_HANDLER_INCLUDED
#define _404_HANDLER_INCLUDED
#include "config_parser.h"
#include "request_handler.h"
class E404Handler: public RequestHandler {
  public:
    const static std::string message;
    void Configure(const NginxConfig& child_config_block);
    std::string HandleRequest(const HTTPRequest& req);
};
#endif
