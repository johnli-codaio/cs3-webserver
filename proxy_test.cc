#include "gtest/gtest.h"
#include "config_parser.h"
#include <sstream>
#include <string>
#include <thread>
#include "ConfigManager.h"
#include "proxy_handler.h"

using namespace std;

// Just a shell based on a unit test I saw. This might not necessarily work,
// since this has threading and what not, and the webserver isn't really working.

bool handleProxy(const HTTPRequest &req,
    const string& url, int port, const string &expected) {
    
    ProxyHandler testHandler;
    size_t domainExists;
    size_t contentExists;

    NginxConfig testConfig;
    shared_ptr<NginxConfigStatement> testStatement (new NginxConfigStatement);

    testStatement->tokens_.push_back("host");
    testStatement->tokens_.push_back(url);
    testStatement->tokens_.push_back(to_string(port));
    testConfig.statements_.push_back(testStatement);
    testHandler.Configure(testConfig);

    string output = testHandler.HandleRequest(req);

    domainExists = output.find(expected);
    contentExists = output.find("Content-Type:");

    if (domainExists == string::npos ||
        contentExists == string::npos)
        return 0;
    return 1;
}

TEST(ProxyServerTest, SimpleProxy) {
    HTTPRequest req;
    req.method = "GET";
    req.path = "/reverse";
    EXPECT_TRUE(handleProxy(req, "www.reddit.com", 80, "domain=.reddit.com"));
}