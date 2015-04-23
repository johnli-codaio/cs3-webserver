all: main

clean: 
	rm -rf *.o *~ testunacceptable testmyalloc \
		testunacceptable.exe testmyalloc.exe

main.o:	main.cc
main:	main.o
	g++ -std=c++0x -g -Wall main.cc -o main -lboost_system
