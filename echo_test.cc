#include "gtest/gtest.h"
#include "config_parser.h"
#include <sstream>
#include <string>
#include <thread>
#include "client.h"
#include "ConfigManager.h"
#include "server.h"

using namespace std;

TEST(EchoServerTest, SimpleEcho) {
    const char* message = "foobar";
    ConfigManager config("example_config");
    int port = config.getPort();
    std::thread t(run, port, false);
    char* reply = send("localhost", (std::to_string(port)).c_str(), message);
    t.join();
    EXPECT_TRUE(strcmp(message, reply));
}

TEST(EchoServerTest, SimpleEcho2) {
    const char* message = "chad be joggin";
    ConfigManager config("example_config");
    int port = config.getPort();
    std::thread t(run, port, false);
    char* reply = send("localhost", (std::to_string(port)).c_str(), message);
    t.join();
    EXPECT_TRUE(strcmp(message, reply));
}

TEST(EchoServerTest, SimpleEcho3) {
    const char* message = "did this pass";
    ConfigManager config("example_config");
    int port = config.getPort();
    std::thread t(run, port, false);
    char* reply = send("localhost", (std::to_string(port)).c_str(), message);
    t.join();
    EXPECT_TRUE(strcmp(message, reply));
}
