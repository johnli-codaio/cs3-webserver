#ifndef _STATIC_HANDLER_INCLUDED
#define _STATIC_HANDLER_INCLUDED
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include "config_parser.h"
#include "request_handler.h"
#include "ConfigManager.h"

class StaticHandler: public RequestHandler {
  public:
    void Configure(const NginxConfig& child_config_block);
    std::string HandleRequest(const HTTPRequest& req);
  private:
    std::string path;
};
#endif
