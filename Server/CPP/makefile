CFLAGS = -g

calendar : reactor_main.o reactor_t.o
	g++ -o reactor reactor_main.o reactor_t.o -lpthread

reactor_main.o : reactor_main.cpp
	g++ -c $(CFLAGS) reactor_main.cpp

reactor_t.o : reactor_t.cpp
	g++ -c $(CFLAGS) reactor_t.cpp -lpthread
