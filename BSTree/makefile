CFLAGS = -ansi -pedantic -g

bstree : bstree.o main.o
	gcc -o bstree bstree.o main.o

bstree.o : bstree.c
	gcc -c $(CFLAGS) bstree.c

main.o : main.c
	gcc -c $(CFLAGS) main.c