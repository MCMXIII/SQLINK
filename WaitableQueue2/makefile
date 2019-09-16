CFLAGS = -ansi -pedantic -g

producerconsumer : producerconsumer.o waitablequeue.o
	gcc -o producerconsumer producerconsumer.o waitablequeue.o -lpthread

producerconsumer.o : producerconsumer.c
	gcc -c $(CFLAGS) producerconsumer.c -lpthread

waitablequeue.o : waitablequeue.c
	gcc -c $(CFLAGS) waitablequeue.c -lpthread