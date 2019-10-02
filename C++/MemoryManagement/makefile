CFLAGS = -ansi -pedantic -g

memorymanagement : memPool_t.o memPage_t.o memManager_t.o main.o
	g++ -o memorymanagement memPool_t.o memPage_t.o memManager_t.o main.o

memPool_t.o : memPool_t.cpp
	g++ -c $(CFLAGS) memPool_t.cpp

memPage_t.o : memPage_t.cpp
	g++ -c $(CFLAGS) memPage_t.cpp

memManager_t.o : memManager_t.cpp
	g++ -c $(CFLAGS) memManager_t.cpp

main.o : main.cpp
	g++ -c $(CFLAGS) main.cpp