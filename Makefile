project3: main.o 
	g++ -o project3 main.o 

main.o: main.cc queue.h linearlist.h linearlist-implementation.h
	g++ -c main.cc
