CFLAGS = -ansi -pedantic -g

hashtable : hashtable.o main.o
	gcc -o hashtable hashtable.o main.o

hashtable.o : hashtable.c
	gcc -c $(CFLAGS) hashtable.c

main.o : main.c
	gcc -c $(CFLAGS) main.c