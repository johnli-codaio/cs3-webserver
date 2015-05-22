#include "ConfigManager.h"
#include <vector>

ConfigManager::ConfigManager(NginxConfig c) {config = c;}

ConfigManager::ConfigManager(const char* file_name) {
    NginxConfigParser config_parser;
    config_parser.Parse(file_name, &config);
}

std::vector<std::shared_ptr<NginxConfigStatement>> ConfigManager::getConfigs() {
  std::vector<std::shared_ptr<NginxConfigStatement>> vect = std::vector<std::shared_ptr<NginxConfigStatement>>();
  for (const std::shared_ptr<NginxConfigStatement>& statement : config.statements_) {
    std::cout << "First token is " << (statement->tokens_)[0] << std::endl;
    if ((statement->tokens_)[0] == "handler") {
      vect.push_back(statement);
    }
  }
  return vect;
}

std::string ConfigManager::getPath(const NginxConfig& config) {
  for (const std::shared_ptr<NginxConfigStatement>& statement : config.statements_) {
    if ((statement->tokens_)[0] == "root") {
      return statement->tokens_[1];
    }
  }
  return "";
}


int ConfigManager::getPort(const NginxConfig& config) {
    int port = -1;
    for (const auto& statement : config.statements_){
        bool listen = false;
        for (std::string token : statement->tokens_){
            if (listen){
                int port = std::stoi(token);
                return port;
            }
            else if (token == "listen"){
                listen = true;
            }
        }
        if ((statement->child_block_).get() != nullptr) {
            port = getPort(*(statement->child_block_));
        }
        if (port > 0) {
            return port;
        }
    }
    return port;
}
