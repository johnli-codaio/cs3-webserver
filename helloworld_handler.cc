#include "helloworld_handler.h"

const std::string HelloWorldHandler::message = 
  "<html><body>Hello, world!</body></html>";

void HelloWorldHandler::Configure(const NginxConfig& child_config_block) {
  return;
}

std::string HelloWorldHandler::HandleRequest(const HTTPRequest& req) {
  return message;
}
