#include <stdlib.h>
#include "hashtable.h"

struct hashNode {
	void* key;
	void* value;
	struct hashNode* next;
};

typedef struct hashNode node;

struct hashTable {
	unsigned long size;
	node** array;
	elementHash hash;
	elementCompare compare;
};

/**************************************
**********Assistant functions**********
**************************************/

node* returnNode(hashTable* t, void* key)
{
	node* listScanner;
	unsigned long cell = (t->hash)(key)%(t->size);
	listScanner = t->array[cell];
	while(listScanner != NULL)
	{
		if((t->compare)(key, (void*)(listScanner->key)) == 0)
		{
			return listScanner;
		}
		listScanner = listScanner->next;
	}
	return NULL;	
}
node* returnPrevious(hashTable* t, node* n)
{
	node* listScanner;
	unsigned long cell = (t->hash)(n->key)%(t->size);
	listScanner = t->array[cell];
	if(listScanner == n)
	{
		return NULL;
	}
	while(listScanner != NULL)
	{
		if(listScanner->next == n)
		{
			return listScanner;
		}
		listScanner = listScanner->next;
	}
	return NULL;	
}

/**************************************
**********Hash Table functions*********
**************************************/

hashTable* hashTableCreate(unsigned long size, elementHash hash, elementCompare compare)
{
	unsigned long i = 0;
	hashTable* t;
	if(size == 0 || hash == NULL || compare == NULL)
	{
		return NULL;
	}
	t = (hashTable*)malloc(sizeof(hashTable));
	if(t == NULL)
	{
		return NULL;
	}
	t->size = size;
	t->hash = hash;
	t->compare = compare;
	t->array = (node**)malloc(t->size*sizeof(node*));
	if(t->array == NULL)
	{
		free(t);
		return NULL;
	}
	for(i = 0; i < t->size; i++)
	{
		t->array[i] = NULL;
	}
	return t;
}
AdtStatus hashTableDestroy(hashTable* t, elementDestroy destroyKey, elementDestroy destroyValue)
{
	unsigned long i = 0;
	node* listCurrent = NULL;
	node* listNext = NULL;
	if(t == NULL || destroyKey == NULL || destroyValue == NULL)
	{
		return UndeclaredError;
	}
	if(t->array == NULL)
	{
		free(t);
		return UndeclaredError;
	}
	for(i = 0; i < t->size; i++)
	{
		if(t->array[i] != NULL)
		{
			listCurrent = t->array[i];
			while(listCurrent != NULL)
			{
				listNext = listCurrent->next;
				if(listCurrent->key != NULL)
				{
					destroyKey(listCurrent->key);
				}
				if(listCurrent->value != NULL)
				{
					destroyValue(listCurrent->value);
				}
				free(listCurrent);
				listCurrent = listNext;
			}
		}
	}
	free(t->array);
	free(t);
	return OK;
}
AdtStatus hashTableInsert(hashTable* t, void* key, void* value, char overwriteValue, elementDestroy destroyValue)
{
	node* keyNode;
	if(t == NULL || t->array == NULL || key == NULL || value == NULL || (overwriteValue == 'y' && destroyValue == NULL))
	{
		return UndeclaredError;
	}
	keyNode = returnNode(t, key);
	if(keyNode == NULL)
	{
		keyNode = (node*)malloc(sizeof(node));
		if(keyNode == NULL)
		{
			return AllocationError;
		}
		keyNode->key = key;
		keyNode->value = value;
		keyNode->next = t->array[(t->hash)(key)%(t->size)];
		t->array[(t->hash)(key)%(t->size)] = keyNode;
	}
	else
	{
		if(overwriteValue == 'y')
		{
			destroyValue((void*)keyNode->value);
			keyNode->value = value;
		}
		else
		{
			return ExistingError;
		}
	}
	return OK;
}
AdtStatus hashTableUpdate(hashTable* t, void* key, void* value, elementDestroy destroyValue)
{
	node* keyNode;
	if(t == NULL || t->array == NULL || key == NULL || value == NULL || destroyValue == NULL)
	{
		return UndeclaredError;
	}
	keyNode = returnNode(t, key);
	if(keyNode == NULL)
	{
		return NotFoundError;
	}
	else
	{
		destroyValue((void*)keyNode->value);
		keyNode->value = value;
	}
	return OK;
}
AdtStatus hashTableDelete(hashTable* t, void* key, elementDestroy destroyKey, elementDestroy destroyValue)
{
	node* keyNode;
	node* keyPrevious;
	if(t == NULL || t->array == NULL || key == NULL || destroyKey == NULL || destroyValue == NULL)
	{
		return UndeclaredError;
	}
	keyNode = returnNode(t, key);
	if(keyNode == NULL)
	{
		return NotFoundError;
	}
	else
	{
		keyPrevious = returnPrevious(t, keyNode);
		if(keyPrevious == NULL)
		{
			t->array[(t->hash)(key)%(t->size)] = keyNode->next;
		}
		else
		{
			keyPrevious->next = keyNode->next;
		}
		if(keyNode->key != NULL)
		{
			destroyKey((void*)(keyNode->key));
		}
		if(keyNode->value != NULL)
		{
			destroyValue((void*)(keyNode->value));
		}
		free(keyNode);
	}
	return OK;
}
void* hashTableFind(hashTable* t, void* key)
{
	node* n;
	if(t == NULL || t->array == NULL || key == NULL)
	{
		return NULL;
	}
	n = returnNode(t, key);
	if(n == NULL)
	{
		return NULL;
	}
	return n->value;
}
int hashTableForEach(hashTable* t, elementAction action)
{
	int i = 0;
	node* listCurrent = NULL;
	if(t == NULL || t->array == NULL || action == NULL)
	{
		return -1;
	}
	for(i = 0; i < t->size; i++)
	{
		if(t->array[i] != NULL)
		{
			listCurrent = t->array[i];
			while(listCurrent != NULL)
			{
				action(i, (void*)listCurrent->key, (void*)listCurrent->value);
				listCurrent = listCurrent->next;
			}
		}
	}
	return 0;
}