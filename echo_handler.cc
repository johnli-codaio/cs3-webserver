#include "echo_handler.h"

void EchoHandler::Configure(const NginxConfig& child_config_block) {
  return;
}

std::string EchoHandler::HandleRequest(const HTTPRequest& req) {
  return unparse(req);
}

std::string EchoHandler::unparse(const HTTPRequest& req) {
  //TODO implement  
  return "";
};
