#include "e404_handler.h"

const std::string E404Handler::message = "Error 404 - File not found";

void E404Handler::Configure(const NginxConfig& child_config_block) {
  return;
}

std::string E404Handler::HandleRequest(const HTTPRequest& req) {
  return message;
}
