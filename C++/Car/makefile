CFLAGS = -ansi -pedantic -g

car : bus.o private.o car.o main.o
	g++ -o car bus.o private.o car.o main.o

bus.o : bus.cpp
	g++ -c $(CFLAGS) bus.cpp

private.o : private.cpp
	g++ -c $(CFLAGS) private.cpp

car.o : car.cpp
	g++ -c $(CFLAGS) car.cpp

main.o : main.cpp
	g++ -c $(CFLAGS) main.cpp