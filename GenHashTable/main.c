#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hashtable.h"

static int nodesCounter = 0;

/**************************************
**********Parameter functions**********
**************************************/

unsigned long hashString(unsigned char *str)
{
        unsigned long hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
}
unsigned long hash(void *key)
{
	return hashString((unsigned char*)key);
}
int compare(void *_elemA, void *_elemB)
{
	return strcmp((char*)_elemA, (char*)_elemB);
}
void stringDestroy(void *_elem)
{
	unsigned char* str = (unsigned char*)_elem;
	if(str != NULL)
	{
		free(str);
	}
}
void printElement(unsigned long hashCell, void* key, void* value)
{
	printf("%lu - %s:%s\n", hashCell, (unsigned char*)key, (unsigned char*)value);
}
void countElements(unsigned long hashCell, void* key, void* value)
{
	nodesCounter++;
}

/**************************************
**********Assistant functions**********
**************************************/

unsigned char* generateRandomKey()
{
	unsigned long i = 0;
	unsigned char* key = (unsigned char*)malloc(10*sizeof(unsigned char));
	if(key == NULL)
	{
		printf("Key cannot be generated!\n");
		return NULL;
	}
	for(i = 0; i < 10; i++)
	{
		key[i] = (rand()%10)+48;
	}
	key[10] = '\0';
	return key;
}
unsigned char* generateRandomValue()
{
	unsigned long i = 0;
	unsigned char* value = (unsigned char*)malloc(10*sizeof(unsigned char));
	if(value == NULL)
	{
		printf("Value cannot be generated!\n");
		return NULL;
	}
	for(i = 0; i < 10; i++)
	{
		value[i] = (rand()%26)+97;
	}
	value[10] = '\0';
	return value;
}
void removeFromArray(int i, unsigned char** arr, int* lengthPtr)
{
	unsigned char* temp = arr[i];
	arr[i] = arr[(*lengthPtr) - 1];
	arr[((*lengthPtr)--) - 1] = NULL;
	if(temp != NULL)
	{
		free(temp);
	}
}
unsigned char** generateFiftyKeys()
{
	int i = 0;
	unsigned char** keys = (unsigned char**)malloc(50*sizeof(unsigned char*));
	if(keys == NULL)
	{
		printf("Cannot generate keys array!\n");
		return NULL;
	}
	for(i = 0; i < 50; i++)
	{
		keys[i] = generateRandomKey();
	}
	return keys;
}
int freeKeysArray(unsigned char** keys)
{
	int i = 0;
	for(i = 0; i < 50; i++)
	{
		if(keys[i] != NULL)
		{
			free(keys[i]);
		}
	}
	free(keys);
	return 0;
}

/**************************************
*************Test functions************
**************************************/

int testCreate(hashTable** t)
{
	*t = hashTableCreate(0, &hash, &compare);
	if(*t != NULL)
	{
		return -1;
	}
	*t = hashTableCreate(16, NULL, &compare);
	if(*t != NULL)
	{
		return -1;
	}
	*t = hashTableCreate(16, &hash, NULL);
	if(*t != NULL)
	{
		return -1;
	}
	*t = hashTableCreate(16, &hash, &compare);
	if(*t != NULL)
	{
		return 0;
	}
	return -1;
}
int testInsert(hashTable* t, unsigned char** keys)
{
	int i = 0;
	int successfulInserts = 0;
	unsigned char str[10] = "123456";
	unsigned char* value = str;
	if(hashTableInsert(NULL, (void*)keys[i], (void*)value, 'n', &stringDestroy) == OK || 
		hashTableInsert(t, NULL, (void*)value, 'n', &stringDestroy) == OK || 
		hashTableInsert(t, (void*)keys[i], NULL, 'n', &stringDestroy) == OK || 
		hashTableInsert(t, (void*)keys[i], (void*)value, 'y', NULL) == OK)
	{
		return -1;
	}
	for(i = 0; i < 30; i++)
	{
		value = generateRandomValue();
		if(hashTableInsert(t, (void*)keys[i], (void*)value, 'n', &stringDestroy) == OK)
		{
			successfulInserts++;
		}
	}
	if(successfulInserts != 30)
	{
		return -1;
	}
	value = generateRandomValue();
	if(hashTableInsert(t, (void*)keys[29], (void*)value, 'n', NULL) != ExistingError)
	{
		return -1;
	}
	if(strcmp((char*)hashTableFind(t, keys[29]), (char*)value) == 0)
	{
		return -1;
	}
	hashTableInsert(t, (void*)keys[29], (void*)value, 'y', &stringDestroy);
	if(strcmp((char*)hashTableFind(t, keys[29]), (char*)value) != 0)
	{
		return -1;
	}
	return 0;
}
int testUpdate(hashTable* t, unsigned char** keys)
{
	int successfulInserts = 0;
	unsigned char str[10] = "123456";
	unsigned char* value = generateRandomValue();
	if(hashTableUpdate(NULL, (void*)keys[0], (void*)value, &stringDestroy) == OK || 
		hashTableUpdate(t, NULL, (void*)value, &stringDestroy) == OK || 
		hashTableUpdate(t, (void*)keys[0], NULL, &stringDestroy) == OK || 
		hashTableUpdate(t, (void*)keys[0], (void*)value, NULL) == OK)
	{
		return -1;
	}
	if(hashTableUpdate(t, (void*)keys[0], (void*)value, &stringDestroy) != OK)
	{
		return -1;
	}
	if(strcmp((char*)hashTableFind(t, keys[0]), (char*)value) != 0)
	{
		return -1;
	}
	if(hashTableUpdate(t, (void*)keys[30], (void*)value, &stringDestroy) != NotFoundError)
	{
		return -1;
	}
	return 0;
}
int testFind(hashTable* t, unsigned char** keys)
{
	int i = 0;
	if(hashTableFind(NULL, keys[i]) != NULL || hashTableFind(t, NULL) != NULL)
	{
		return -1;
	}
	for(i = 0; i < 30; i++)
	{
		if(hashTableFind(t, keys[i]) == NULL)
		{
			return -1;
		}
	}
	for(i = 30; i < 50; i++)
	{
		if(hashTableFind(t, keys[i]) != NULL)
		{
			return -1;
		}
	}
	return 0;
}
int testForEach(hashTable* t)
{
	if(hashTableForEach(NULL, &countElements) != -1 || hashTableForEach(t, NULL) != -1)
	{
		return -1;
	}
	nodesCounter = 0;
	hashTableForEach(t, &countElements);
	if(nodesCounter != 30)
	{
		return -1;
	}
	return 0;
}
int testDelete(hashTable* t, unsigned char** keys, int* arrayLength)
{
	int i = 0;
	int j = 0;
	int beforeDelete = 0;
	int afterDelete = 0;
	int removals = 0;
	nodesCounter = 0;
	hashTableForEach(t, &countElements);
	beforeDelete = nodesCounter;
	if(hashTableDelete(NULL, (void*)keys[j], &stringDestroy, &stringDestroy) == OK || 
		hashTableDelete(t, NULL, &stringDestroy, &stringDestroy) == OK || 
		hashTableDelete(t, (void*)keys[j], NULL, &stringDestroy) == OK || 
		hashTableDelete(t, (void*)keys[j], &stringDestroy, NULL) == OK)
	{
		return -1;
	}
	for(i = 0; i < 20; i++)
	{
		j = rand()%(*arrayLength);
		if(hashTableFind(t, keys[j]) != NULL)
		{
		
			if(hashTableDelete(t, keys[j], &stringDestroy, &stringDestroy) == OK)
			{
				if(hashTableFind(t, keys[j]) != NULL)
				{
					return -1;
				}
				removals++;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			if(hashTableDelete(t, keys[j], &stringDestroy, &stringDestroy) == OK)
			{
				return -1;
			}
		}
		removeFromArray(j, keys, arrayLength);
	}
	nodesCounter = 0;
	hashTableForEach(t, &countElements);
	afterDelete = nodesCounter;
	if(beforeDelete - afterDelete != removals)
	{
		return -1;
	}
	return 0;
}
int testDestroy(hashTable* t)
{
	if(hashTableDestroy(NULL, &stringDestroy, &stringDestroy) == OK || 
		hashTableDestroy(t, NULL, &stringDestroy) == OK ||
		hashTableDestroy(t, &stringDestroy, NULL) == OK)
	{
		return -1;
	}
	if(hashTableDestroy(t, &stringDestroy, &stringDestroy) != OK)
	{
		return -1;
	}
	return 0;
}

/**************************************
*************Main function*************
**************************************/

int main()
{
	int i = 0;
	int arrayLength = 50;
	int j = 0;
	unsigned char* key;
	unsigned char** keys;
	unsigned char* value;
	hashTable* t;
	srand(time(0));
	keys = generateFiftyKeys();
	printf(testCreate(&t) == 0?"Create is OK!\n":"Problems in create!\n");
	printf(testInsert(t, keys) == 0?"Insert is OK!\n":"Problems in insert!\n");
	printf(testUpdate(t, keys) == 0?"Update is OK!\n":"Problems in update!\n");
	printf(testFind(t, keys) == 0?"Find is OK!\n":"Problems in Find!\n");
	printf(testForEach(t) == 0?"Foreach is OK!\n":"Problems in foreach!\n");
	printf(testDelete(t, keys, &arrayLength) == 0?"Delete is OK!\n":"Problems in delete!\n");
	printf(testDestroy(t) == 0?"Destroy is OK!\n":"Problems in destroy!\n");
	for(i = 0; i < 50; i++)
	{
		if(keys[i] != NULL)
		{
			free(keys[i]);
		}
	}
	freeKeysArray(keys);
	return 0;
}