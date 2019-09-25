CFLAGS = -ansi -pedantic -g

car : bus.o car.o main.o
	g++ -o car bus.o car.o main.o

bus.o : bus.cpp
	g++ -c $(CFLAGS) bus.cpp

car.o : car.cpp
	g++ -c $(CFLAGS) car.cpp

main.o : main.cpp
	g++ -c $(CFLAGS) main.cpp
