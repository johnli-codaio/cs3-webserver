GTEST_DIR=gtest-1.7.0

all: hello_world_server echo_server

clean: 
	rm -rf *.o *~ hello_world_server echo_server clienttest test

config_parser.o: config_parser.cc
	g++ -Wall -g -c -std=c++0x config_parser.cc

main.o:	main.cc
	g++ -Wall -std=c++0x -g -Wall -c main.cc

echo_test.o: echo_test.cc
	g++ -Wall -g -I gtest-1.7.0/include -c -std=c++0x echo_test.cc
	
echo.o : echo.cc
	g++ -Wall -g -c -std=c++0x echo.cc
	
hello_world.o : hello_world.cc
	g++ -Wall -g -c -std=c++0x hello_world.cc

client.o : client.cc
	g++ -Wall -g -c -std=c++0x client.cc

ConfigManager.o : ConfigManager.cc
	g++ -Wall -g -c -std=c++0x ConfigManager.cc
	
clienttest.o : clienttest.cc
	g++ -Wall -g -c -std=c++0x clienttest.cc
	
echo_server: echo.o main.o config_parser.o ConfigManager.o
	g++ -std=c++0x -g -Wall echo.o main.o ConfigManager.o config_parser.o -o \
	echo_server -lboost_system -lpthread

hello_world_server:	main.o ConfigManager.o config_parser.o hello_world.o
	g++ -std=c++0x -g -Wall main.o hello_world.o ConfigManager.o \
	config_parser.o -o hello_world_server -lboost_system
	
clienttest: clienttest.o client.o ConfigManager.o config_parser.o echo.o
	g++ -Wall -g -std=c++0x clienttest.o client.o ConfigManager.o \
	config_parser.o echo.o  -o clienttest -lboost_system -lpthread


test: echo_test.o config_parser.o client.o ConfigManager.o echo.o
	g++ -std=c++0x -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -pthread -c ${GTEST_DIR}/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o
	g++ -std=c++0x -isystem ${GTEST_DIR}/include -pthread echo_test.o config_parser.o client.o ConfigManager.o echo.o ${GTEST_DIR}/src/gtest_main.cc libgtest.a -o test -lpthread -lboost_system
