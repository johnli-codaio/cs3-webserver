all: hello_world_server echo_server test

clean: 
	rm -rf *.o *~ webserver echo_server

config_parser.o: config_parser.cc
	g++ -Wall -g -c -std=c++0x config_parser.cc

main.o:	main.cc
	g++ -Wall -std=c++0x -g -Wall -c main.cc

echo_test.o: echo_test.cc
	g++ -Wall -g -c -std=c++0x echo_test.cc
	
echo.o : echo.cc
	g++ -Wall -g -c -std=c++0x echo.cc
	
hello_world.o : hello_world.cc
	g++ -Wall -g -c -std=c++0x hello_world.cc

ConfigManager.o : ConfigManager.cc
	g++ -Wall -g -c -std=c++0x ConfigManager.cc
	
echo_server: echo.o main.o ConfigManager.o config_parser.o
	g++ -std=c++0x -g -Wall echo.o main.o ConfigManager.o config_parser.o -o \
	echo_server -lboost_system -lpthread

hello_world_server:	main.o hello_world.o config_parser.o
	g++ -std=c++0x -g -Wall main.o hello_world.o ConfigManager.o \
	config_parser.o -o hello_world_server -lboost_system 

test: echo_test.o
	g++ -std=c++0x -g -Wall echo_test.o -o echo_test -lboost_system -lpthread
	./echo_test
