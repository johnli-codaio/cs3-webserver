#include "static_handler.h"

void StaticHandler::Configure(const NginxConfig& child_config_block) {
  path = ConfigManager.getPath(child_config_block)
}

std::string StaticHandler::HandleRequest(const HTTPRequest& req) {
  std::string filename = path + req.path;
  struct stat buffer;   
  bool found = (stat (filename.c_str(), &buffer) == 0);
  if (found) {
        std::ifstream file(static_path + request);
        std::string buffer;
        std::string requested_file;
        while (std::getline(file, buffer)) {
          requested_file += buffer;
          requested_file.push_back('\n');
        }
        return requested_file;
  }
  else {
    return "Error 404 - File not found"
  }
}
