#include "ConfigManager.h"
#include <string>

ConfigManager::ConfigManager(NginxConfig c) {config = c;}

ConfigManager::ConfigManager(const char* file_name) {
    NginxConfigParser config_parser;
    config_parser.Parse(file_name, &config);
}

int ConfigManager::getPort(NginxConfig& config) {
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

std::string ConfigManager::getBaseDirectory(NginxConfig& config) {
    std::string base = "";
    for (const auto& statement : config.statements_){
        bool base_bool = false;
        for (std::string token : statement->tokens_){
            if (base_bool){
                std::string base = token;
                return base;
            }
            else if (token == "base"){
                base_bool = true;
            }
        }
        if ((statement->child_block_).get() != nullptr) {
            base = getBaseDirectory(*(statement->child_block_));
        }
        if (base != "") {
            return base;
        }
    }
    return base;
}
