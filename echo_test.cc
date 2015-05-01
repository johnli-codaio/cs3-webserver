#include "gtest/gtest.h"
#include "config_parser.h"
#include <sstream>
#include <string>

using namespace std;

// Initial test that was already given
TEST(NginxConfigParserTest, SimpleConfig) {
  string first = "<html><body>Hello, world!</body></html>";

  EXPECT_EQ("<html><body>Hello, world!</body></html>");
}

// Initial test that was already given
TEST(NginxConfigParserTest, SimpleConfig) {
  string first = "<html><body>Test number 2</body></html>";

  EXPECT_EQ("<html><body>Test number 2</body></html>");
}

// Initial test that was already given
TEST(NginxConfigParserTest, SimpleConfig) {
  string first = "<html><body>Test 3</body></html>";

  EXPECT_EQ("<html><body>Test 3</body></html>");
}

// Initial test that was already given
TEST(NginxConfigParserTest, SimpleConfig) {
  string first = "<html><body>Test 4</body></html>";

  EXPECT_EQ("<html><body>Test 4</body></html>");
}
