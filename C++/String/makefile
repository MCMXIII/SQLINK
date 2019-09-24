CFLAGS = -ansi -pedantic -g

stringtype : stringtype.o main.o
	g++ -o stringtype stringtype.o main.o

stringtype.o : stringtype.cpp
	g++ -c $(CFLAGS) stringtype.cpp

main.o : main.cpp
	g++ -c $(CFLAGS) main.cpp
