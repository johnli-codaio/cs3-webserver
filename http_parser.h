#ifndef _HTTP_PARSER_INCLUDED
#define _HTTP_PARSER_INCLUDED

#include "request_handler.h"

HTTPRequest parseRequest(std::string request);

#endif
