#include "http_parser.h"
#include <string>
#include <iostream>

HTTPRequest parseRequest(std::string request) {
  std::string processed;
  int index1;
  HTTPRequest req;
  std::vector<std::pair<std::string, std::string>> headers;

  index1 = request.find_first_of(' ');
  req.method = request.substr(0, index1);
  request = request.substr(++index1);

  //std::cout << request << std::endl;

  index1 = request.find_first_of(' ');
  req.path = request.substr(0, index1);

  index1 = request.find_first_of('\n');
  request = request.substr(++index1);

  while (request[0] != '\n') {
  	std::string header1, header2;

  	index1 = request.find_first_of(':');
  	header1 = request.substr(0, index1);
    request = request.substr(++index1);

    index1 = request.find_first_of('\n');
    header2 = request.substr(0, index1);
    request = request.substr(++index1);

    std::pair<std::string, std::string> to_emplace = {header1, header2};
  	headers.emplace_back(to_emplace);
  }

  req.headers = headers;

  req.request_body = request;

  return req;
}