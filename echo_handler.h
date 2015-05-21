#ifndef _ECHO_HANDLER_INCLUDED
#define _ECHO_HANDLER_INCLUDED
#include "config_parser.h"
#include "request_handler.h"
class EchoHandler: public RequestHandler {
  public:
    void Configure(const NginxConfig& child_config_block);
    std::string HandleRequest(const HTTPRequest& req);
  private:
    std::string unparse(const HTTPRequest& req);
};
#endif
