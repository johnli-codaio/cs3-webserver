#ifndef _HTTP_PARSER_INCLUDED
#define _HTTP_PARSER_INCLUDED

HTTPRequest parseRequest(std::string request);
std::string unparseRequest(HTTPRequest request);

#endif
