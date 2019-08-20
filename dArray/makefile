CFLAGS = -ansi -pedantic -g

darray : darray_int.o darray_test.o
	gcc -o darray darray_int.o darray_test.o

darray_int.o : darray_int.c
	gcc -c $(CFLAGS) darray_int.c

darray_test.o : darray_test.c
	gcc -c $(CFLAGS) darray_test.c