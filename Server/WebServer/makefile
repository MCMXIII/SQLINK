CFLAGS = -g

webserver-epoll : webserver-epoll.o
	gcc -o webserver-epoll webserver-epoll.o -lpthread

webserver : webserver.o
	gcc -o webserver webserver.o -lpthread

webserver-epoll.o : webserver-epoll.c
	gcc -c $(CFLAGS) webserver-epoll.c -lpthread

webserver.o : webserver.c
	gcc -c $(CFLAGS) webserver.c -lpthread
