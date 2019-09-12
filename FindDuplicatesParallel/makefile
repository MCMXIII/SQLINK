CFLAGS = -ansi -g

finddup : md5.o hashtable.o fileOps.o init.o findDup.o
	gcc -o finddup md5.o hashtable.o fileOps.o init.o findDup.o -lcrypto -pthread

findDup.o : findDup.c
	gcc -c $(CFLAGS) findDup.c

init.o : init.c
	gcc -c $(CFLAGS) init.c

fileOps.o : fileOps.c
	gcc -c $(CFLAGS) fileOps.c -pthread

hashtable.o : hashtable.c
	gcc -c $(CFLAGS) hashtable.c

md5.o : md5.c
	gcc -c $(CFLAGS) md5.c -lcrypto