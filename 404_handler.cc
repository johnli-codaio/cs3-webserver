#include "helloworld_handler.h"

const std::string 404Handler::message = "Error 404 - File not found";

void 404Handler::Configure(const NginxConfig& child_config_block) {
  return;
}

std::string 404Handler::HandleRequest(const HTTPRequest& req) {
  return message;
}
