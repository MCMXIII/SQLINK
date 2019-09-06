#ifndef HASHTABLE_H
#define HASHTABLE_H

	typedef unsigned long (* elementHash)(void *key);
	typedef int (* elementCompare)(void *_elemA, void *_elemB);
	typedef void (* elementDestroy)(void *_elem);
	typedef void (* elementAction)(unsigned long hashCell, void *key, void *value);
	typedef enum  {OK, AllocationError, IndexError, AmountError, UndeclaredError, NotFoundError, ExistingError} AdtStatus;
	typedef struct hashTable hashTable;

	hashTable* hashTableCreate(unsigned long size, elementHash hash, elementCompare compare);
	AdtStatus hashTableDestroy(hashTable* t, elementDestroy destroyKey, elementDestroy destroyValue);
	AdtStatus hashTableInsert(hashTable* t, void* key, void* value, char overwriteValue, elementDestroy destroyValue);
	AdtStatus hashTableUpdate(hashTable* t, void* key, void* value, elementDestroy destroyValue);
	AdtStatus hashTableDelete(hashTable* t, void* key, elementDestroy destroyKey, elementDestroy destroyValue);
	void* hashTableFind(hashTable* t, void* key);
	int hashTableForEach(hashTable* t, elementAction action);

#endif