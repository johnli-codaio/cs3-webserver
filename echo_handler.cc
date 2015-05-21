#include "echo_handler.h"
#include <string>

void EchoHandler::Configure(const NginxConfig& child_config_block) {
  return;
}

std::string EchoHandler::HandleRequest(const HTTPRequest& req) {
  return unparse(req);
}

std::string EchoHandler::unparse(const HTTPRequest& req) {
  string unparsed = "";

  unparsed += method + " ";
  unparsed += path + " HTTP/1.1\n";
  int num_headers = headers.size();

  for (int i = 0; i < num_headers; ++i) {
  	unparsed += headers[i].first + ": " + headers[i].second + "\n";
  }

  unparsed += "\n";

  unparsed += request_body;

  return unparsed;
};
