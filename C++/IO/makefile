CFLAGS = -ansi -pedantic -g

io : io.o asciiIO_t.o binIO_t.o
	g++ -o io io.o asciiIO_t.o binIO_t.o

io.o : io.cpp
	g++ -c $(CFLAGS) io.cpp

asciiIO_t.o : asciiIO_t.cpp
	g++ -c $(CFLAGS) asciiIO_t.cpp

binIO_t.o : binIO_t.cpp
	g++ -c $(CFLAGS) binIO_t.cpp