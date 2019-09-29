CFLAGS = -ansi -pedantic -g

memorymanagement : memPage_t.o memManager_t.o main.o
	g++ -o memorymanagement memPage_t.o memManager_t.o main.o

memPage_t.o : memPage_t.cpp
	g++ -c $(CFLAGS) memPage_t.cpp

memManager_t.o : memManager_t.cpp
	g++ -c $(CFLAGS) memManager_t.cpp

main.o : main.cpp
	g++ -c $(CFLAGS) main.cpp