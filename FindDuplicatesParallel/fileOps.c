#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include "md5.h"
#include "fileOps.h"

typedef struct {
	unsigned char* key;
	char* path;
} keyPath;
typedef struct {
	keyPath* kpQueue;
	unsigned int amount;
	sem_t full;
	sem_t empty;
	pthread_mutex_t mutex;
} queue;
queue q;
unsigned int finished = 0;
pthread_mutex_t hashMutex[256];
typedef enum {
	DIRECTORY = 4,
	REGFILE = 8
} filetype;
void doNothing(void* element)
{
	return;
}
void zeroString(char* str, int len)
{
	int i;
	for(i = 0; i < len - 1; i++)
	{
		str[i] = 0;
	}
	str[len - 1] = '\0';
}
void findOrAdd(hashTable* t/*, FILE* output*/)
{
	unsigned char* key;
	char* path;
	char* value;
	unsigned char* tableKey;
	while(1)
	{
		if(sem_trywait(&(q.empty)) == 0)
		{
			break;
		}
		if(q.amount == 0 && finished)
		{
			return;
		}
	}
	pthread_mutex_lock(&(q.mutex));
	sem_post(&(q.full));
	key = q.kpQueue->key;
	path = q.kpQueue->path;
	q.amount--;
	pthread_mutex_unlock(&(q.mutex));
	if(path == NULL)
	{
		if(key != NULL)
			free(key);
		return;
	}
	pthread_mutex_lock(&hashMutex[hash((void*)key)%256]);
	if(hashTableFind(t, key) != NULL)
	{
		printf("%s is a duplicate file of %s!\n", path, (char*)hashTableFind(t, key));
		/*fprintf(output, "%s is a duplicate file of %s!\n", path, (char*)hashTableFind(t, key));*/
	}
	else
	{
		tableKey = (unsigned char*)malloc((strlen(key)+1)*sizeof(unsigned char));
		if(tableKey == NULL)
		{
			printf("Error in hashing key!\n");
			/*fprintf(output, "Error in hashing key!\n");*/
		}
		else
		{
			strcpy(tableKey, key);
			value = (char*)malloc((strlen(path)+1)*sizeof(char));
			if(value == NULL)
			{
				printf("Error in hashing value!\n");
				/*fprintf(output, "Error in hashing value!\n");*/
				free(tableKey);
			}
			else
			{
				strcpy(value, path);
				if(hashTableInsert(t, (void*)tableKey, (void*)value, 'n', doNothing) != OK)
				{
					printf("Error in hashing!\n");
					/*fprintf(output, "Error in hashing!\n");*/
				}
			}
		}
	}
	pthread_mutex_unlock(&hashMutex[hash((void*)key)%256]);
	free(key);
	free(path);
}
void findDuplicates(const char *name, hashTable* t, unsigned int isFirstCall/*, FILE* output*/)
{
	DIR *dir;
	struct dirent *entry;
	char path[1024];
	unsigned char key[17];
	FILE* f;
	if(name[0] == '\0')
	{
		return;
	}
	if (!(dir = opendir(name)))
	{
		return;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		zeroString(path, 1024);
		snprintf(path, sizeof(path), "%s/%s\0", name, entry->d_name);
		if (entry->d_type == DIRECTORY)
		{
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			{
				continue;
			}
			findDuplicates(path, t/*, output*/, 0);
		}
		else if(entry->d_type == REGFILE)
		{
			if(strcmp(path, "./duplicates.txt") == 0)
			{
				continue;
			}
			f = fopen(path, "rb");
			if(f == NULL)
			{
				printf("Error in opening file!\n");
				/*fprintf(output, "Error in opening file!\n");*/
				continue;
			}
			zeroString(key, 17);
			generateKey(f, key);
			while(1)
			{
				if(sem_trywait(&(q.full)) == 0)
				{
					break;
				}
			}
			pthread_mutex_lock(&(q.mutex));
			sem_post(&(q.empty));
			q.kpQueue->key = (unsigned char*)malloc((strlen(key)+1)*sizeof(unsigned char));
			q.kpQueue->path = (char*)malloc((strlen(path)+1)*sizeof(char));
			strcpy(q.kpQueue->key, key);
			q.kpQueue->key[strlen(key)] = '\0';
			strcpy(q.kpQueue->path, path);
			q.kpQueue->path[strlen(path)] = '\0';
			q.amount++;
			pthread_mutex_unlock(&(q.mutex));
			/*findOrAdd(t, key, path, output);*/
			fclose(f);
		}
	}
	closedir(dir);
	finished = isFirstCall?1:0;
}
void* mainThread(void* t)
{
	findDuplicates(".", (hashTable*)t, 1/*, FILE* output*/);
	return;
}
void* subThread(void* t)
{
	while(!finished || q.amount > 0)
	{
		findOrAdd((hashTable*)t);
	}
}
void callThreads(hashTable* t)
{
	int i = 0;
	pthread_t hashThreads[8];
	pthread_t mainT;
	q.kpQueue = (keyPath*)malloc(sizeof(keyPath));
	q.amount = 0;
	sem_init(&(q.full), 0, 1);	
	sem_init(&(q.empty), 0, 1);
	sem_wait(&(q.empty));
	pthread_mutex_init(&(q.mutex), NULL);
	for(i = 0; i < 256; i++)
	{
		pthread_mutex_init(&(hashMutex[i]), NULL);
	}
	pthread_create(&(mainT), NULL, &mainThread, (void*)t);
	for(i = 0; i < 8; i++)
	{
		pthread_create(&(hashThreads[i]), NULL, &subThread, (void*)t);
	}
	pthread_join(mainT, NULL);
	for(i = 0; i < 8; i++)
	{
		pthread_join(hashThreads[i], NULL);
	}
}