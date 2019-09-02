CFLAGS = -ansi -pedantic -g
LD_LIBRARY_PATH = .

executable : progA.o progB.o libN.so
	gcc -o executable progA.o progB.o libN.so

progA.o : progA.c libN.so
	gcc -c $(CFLAGS) progA.c -lN -L. 

progB.o : progB.c
	gcc -c $(CFLAGS) progB.c

libN.so : lib1.o lib2.o lib3.o
	gcc -shared -o libN.so $(CFLAGS)  lib1.o lib2.o lib3.o

lib1.o : lib1.c
	gcc -c -fpic $(CFLAGS) lib1.c

lib2.o : lib2.c
	gcc -c -fpic $(CFLAGS) lib2.c

lib3.o : lib3.c
	gcc -c -fpic $(CFLAGS) lib3.c