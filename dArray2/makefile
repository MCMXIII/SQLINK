CFLAGS = -ansi -pedantic -g

darray : darray.o darray_test.o
	gcc -o darray darray.o darray_test.o

darray.o : darray.c
	gcc -c $(CFLAGS) darray.c

darray_test.o : darray_test.c
	gcc -c $(CFLAGS) darray_test.c