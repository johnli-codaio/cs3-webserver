all: webserver test

clean: 
	rm -rf *.o *~ webserver echo_server

config_parser.o: config_parser.cc
	g++ -Wall -g -c -std=c++0x config_parser.cc

main.o:	main.cc
	g++ -Wall -std=c++0x -g -Wall -c main.cc

echo_test.o: echo_test.cc
	g++ -Wall -g -c -std=c++0x echo_test.cc

webserver:	main.o config_parser.o
	g++ -std=c++0x -g -Wall main.o config_parser.o -o webserver -lboost_system

test: echo_test.o
	g++ -std=c++0x -g -Wall echo_test.o -o echo_test -lboost_system -lpthread
	./echo_test