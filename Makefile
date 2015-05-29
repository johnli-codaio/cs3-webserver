GTEST_DIR=gtest-1.7.0
OBJECTS = e404_handler.o helloworld_handler.o echo_handler.o static_handler.o \
config_parser.o proxy_handler.o ConfigManager.o main.o http_parser.o

all: webserver

clean: 
	rm -rf *.o *~ hello_world_server echo_server clienttest test webserver \
	server

e404_handler.o: e404_handler.cc
	g++ -Wall -g -c -std=c++0x e404_handler.cc

helloworld_handler.o: helloworld_handler.cc
	g++ -Wall -g -c -std=c++0x helloworld_handler.cc

echo_handler.o: echo_handler.cc
	g++ -Wall -g -c -std=c++0x echo_handler.cc

static_handler.o: static_handler.cc
	g++ -Wall -g -c -std=c++0x static_handler.cc

proxy_handler.o: proxy_handler.cc
	g++ -Wall -g -c -std=c++0x proxy_handler.cc

config_parser.o: config_parser.cc
	g++ -Wall -g -c -std=c++0x config_parser.cc

main.o:	main.cc
	g++ -Wall -std=c++0x -g -Wall -c main.cc -pthread

echo_test.o: echo_test.cc
	g++ -Wall -g -I gtest-1.7.0/include -c -std=c++0x echo_test.cc

proxy_test.o: proxy_test.cc
	g++ -Wall -g -I gtest-1.7.0/include -c -std=c++0x proxy_test.cc


ConfigManager.o : ConfigManager.cc
	g++ -Wall -g -c -std=c++0x ConfigManager.cc
	
clienttest.o : clienttest.cc
	g++ -Wall -g -c -std=c++0x clienttest.cc

echo_handler_unparser_tests.o : echo_handler_unparser_tests.cc
	g++ -Wall -g -c -std=c++0x echo_handler_unparser_tests.cc

http_parser_tests.o : http_parser_tests.cc
	g++ -Wall -g -c -std=c++0x http_parser_tests.cc

http_parser.o : http_parser.cc
	g++ -Wall -g -c -std=c++0x http_parser.cc
	
webserver: ${OBJECTS}
	g++ -std=c++0x -g -Wall ${OBJECTS} -o webserver -lboost_system -lboost_thread -pthread

test: proxy_test.o echo_test.o config_parser.o client.o ConfigManager.o echo.o
	g++ -std=c++0x -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -pthread -c \
	${GTEST_DIR}/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o
	g++ -std=c++0x -isystem ${GTEST_DIR}/include -pthread echo_test.o \
	config_parser.o client.o ConfigManager.o echo.o \
	${GTEST_DIR}/src/gtest_main.cc libgtest.a -o test -lpthread -lboost_system
	./test

unparser_test: config_parser.o echo_handler_unparser_tests.o ConfigManager.o echo_handler.o
	g++ -Wall -g -std=c++0x config_parser.o ConfigManager.o echo_handler.o \
	echo_handler_unparser_tests.o -o unparser_test -lboost_system -lpthread

parser_test: config_parser.o http_parser_tests.o ConfigManager.o http_parser.o
	g++ -Wall -g -std=c++0x config_parser.o ConfigManager.o http_parser.o \
	http_parser_tests.o -o parser_test -lboost_system -lpthread
