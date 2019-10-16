CFLAGS = -ansi -pedantic -g

calendar : calendar.o calendar_t.o
	g++ -o calendar calendar.o calendar_t.o

calendar.o : calendar.cpp
	g++ -c $(CFLAGS) calendar.cpp

calendar_t.o : calendar_t.cpp
	g++ -c $(CFLAGS) calendar_t.cpp