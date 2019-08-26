#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

unsigned long hashString(char *str)
{
        unsigned long hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
}
unsigned long hash(void *key)
{
	return hashString((char*)key);
}
int compare(void *_elemA, void *_elemB)
{
	return strcmp((char*)_elemA, (char*)_elemB);
}
void stringDestroy(void *_elem)
{
	char* str = (char*)_elem;
	if(str != NULL)
	{
		free(str);
	}
}
void printElement(void *_elem)
{
	printf("%s ", (char*)_elem);
}

int main()
{
	char* key = (char*)malloc(10*sizeof(char));
	char* value = (char*)malloc(10*sizeof(char));
	hashTable* t;
	t = hashTableCreate(10, &hash, &compare);
	strcpy(key, "123456789");
	strcpy(value, "abcdefghi");
	hashTableInsert(t, (void*)key, (void*)value, 'n');
	hashTableForEach(t, &printElement);
	printf("\n");
	hashTableDestroy(t, &stringDestroy, &stringDestroy);
	return 0;
}