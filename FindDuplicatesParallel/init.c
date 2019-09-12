#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "md5.h"
#include "init.h"

int elementsCompare(void* k1, void* k2)
{
	return strcmp((unsigned char*)k1, (unsigned char*)k2);
}

void mallocDestroy(void* obj)
{
	free(obj);
}

hashTable* initializeHashTable()
{
	hashTable* t = hashTableCreate(65536, &hash, &elementsCompare);
	if(t == NULL)
	{
		printf("Error in creating hash table!\n");
	}
	return t;
}

void destroyHashTable(hashTable* t)
{
	if(hashTableDestroy(t, &mallocDestroy, &mallocDestroy) != OK)
	{
		printf("Error in destroying hash table!\n");
	}
}