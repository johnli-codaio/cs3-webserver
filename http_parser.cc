#include "http_parser.h"
#include <string>

HTTPRequest parseRequest(std::string request) {
  string processed;
  int index1, index2;
  HTTPRequest req;
  vector<pair<string, string>> headers;

  index1 = request.find_first_of(' ');
  req.method = request.substr(0, index1);

  index2 = request.find_first_of(' ');
  req.path = request.substr(++index1, index2);

  index1 = find_first_of('\n');
  request = request.substr(++index1);

  int i = 0;
  while (request != "") {
  	string header1, header2;
  	index1 = find_first_of(':');
  	header1 = request.substr(0, index1);
  	index2 = find_first_of('\n');
  	header2 = request.substr(++index1, index2);
  	headers.emplace_back({header1, header2});
  }
  req.headers = headers;

  return req;
}
