#include "helloworld_handler.h"
#include "e404_handler.h"
#include "echo_handler.h"
#include "static_handler.h"
#include <unordered_map>

int main() {
    HTTPRequest request = {"GET", "/html/chad.txt", {{"foo1", "bar2"}}, ""};
    ConfigManager config("example_config");
    std::unordered_map<std::string,RequestHandler*> handlers = std::unordered_map<std::string,RequestHandler*>();
    std::vector<std::shared_ptr<NginxConfigStatement>> handlerConfigs = config.getConfigs();
    std::vector<std::shared_ptr<NginxConfigStatement>>::iterator it;
    for ( it = handlerConfigs.begin(); it != handlerConfigs.end(); it++) {
      std::string type = ((*it)->tokens_)[1];
      if (type.compare("helloworld") == 0) {
        handlers[((*it)->tokens_)[2]] = new HelloWorldHandler();
      }
      else if (type.compare("echo") == 0) {
        handlers[((*it)->tokens_)[2]] = new EchoHandler();
      }
      else if (type.compare("static") == 0) {
        RequestHandler* handler = new StaticHandler();
        handler->Configure(*((*it)->child_block_));
        handlers[((*it)->tokens_)[2]] = handler;
      }
      else {
        std::cerr << "Unsupported handler type " << type << " encountered.\n";
      }
    }
    handlers["404"] = new E404Handler();
    std::string output;
    std::string binding = "/html";
    std::string response;
    if (handlers.find(binding) == handlers.end() ) {
      std::cout << "Hanlder not found" << std::endl;
      binding = "404";
    }
    response = handlers[binding] -> HandleRequest(request);
    std::cout << response << std::endl;
    return 0;
}
