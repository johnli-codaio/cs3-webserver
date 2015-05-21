#include "echo_handler.h"
#include <string>

void EchoHandler::Configure(const NginxConfig& child_config_block) {
  return;
}

std::string EchoHandler::HandleRequest(const HTTPRequest& req) {
  return unparse(req);
}

std::string EchoHandler::unparse(const HTTPRequest& req) {
  std::string unparsed = "";

  unparsed += req.method + " ";
  unparsed += req.path + " HTTP/1.1\n";
  int num_headers = req.headers.size();

  for (int i = 0; i < num_headers; ++i) {
  	unparsed += req.headers[i].first + ": " + req.headers[i].second + "\n";
  }

  unparsed += "\n";

  unparsed += req.request_body;

  return unparsed;
};
