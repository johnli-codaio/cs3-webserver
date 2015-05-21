#include "helloworld_handler.h"

void HelloWorldHandler::Configure(const NginxConfig& child_config_block) {
  return;
}

std::string HelloWorldHandler::HandleRequest(const HTTPRequest& req) {
  return message;
}
