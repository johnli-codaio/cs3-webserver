all: webserver

clean: 
	rm -rf *.o *~ webserver

config_parser.o: config_parser.cc
	g++ -Wall -g -c -std=c++0x config_parser.cc

main.o:	main.cc
	g++ -Wall -std=c++0x -g -Wall -c main.cc

webserver:	main.o config_parser.o
	g++ -std=c++0x -g -Wall main.o config_parser.o -o webserver -lboost_system
