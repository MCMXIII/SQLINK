#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "waitablequeue.h"

struct waitableQueue {
	void** queue;
	unsigned int amount;
	unsigned int started;	
	unsigned int finished;
	int fThreads;
	sem_t full;
	sem_t empty;	
	pthread_mutex_t mutex;
};

waitableQueue queueCreate(unsigned int size)
{
	int i;
	waitableQueue q;
	q = (waitableQueue)malloc(sizeof(struct waitableQueue));
	if(q == NULL)
	{
		return NULL;
	}
	q->queue = (void**)malloc(size*sizeof(void*));
	if(q->queue == NULL)
	{
		free(q);
		return NULL;
	}
	q->amount = 0;
	q->started = 0;	
	q->finished = 0;
	q->fThreads = 0;
	sem_init(&(q->full), 0, size);	
	sem_init(&(q->empty), 0, size);
	for(i = 0; i < size; i++)
	{
		sem_wait(&(q->empty));
		q->queue[i] = NULL;
	}
	pthread_mutex_init(&(q->mutex), NULL);
	return q;
}
void* readFromQueue(waitableQueue q)
{
	int i;
	void* message;
	if(q == NULL || q->queue == NULL)
	{
		return NULL;
	}
	while(!(q->started)){
	}
	while(1)
	{
		if(sem_trywait(&(q->empty)) == 0)
		{
			break;
		}
		if(q->amount == 0 && q->finished == 1)
		{
			return NULL;
		}

	}
	pthread_mutex_lock(&(q->mutex));
	sem_post(&(q->full));
	message = q->queue[0];
	for(i = 0; i < q->amount; i++)
	{
		q->queue[i] = q->queue[i + 1];
	}
	q->queue[--q->amount] = NULL;
	pthread_mutex_unlock(&(q->mutex));
	return message;
}
int writeToQueue(waitableQueue q, void* message)
{
	if(q == NULL || q->queue == NULL)
	{
		return -1;
	}
	sem_wait(&(q->full));
	pthread_mutex_lock(&(q->mutex));
	sem_post(&(q->empty));
	q->queue[q->amount++] = message;
	q->started = 1;
	pthread_mutex_unlock(&(q->mutex));
	return 0;
}
unsigned int getAmount(waitableQueue q)
{
	if(q == NULL || q->queue == NULL)
	{
		return 0;
	}
	return q->amount;
}
int destroyQueue(waitableQueue q)
{
	if(q == NULL)
	{
		return -1;
	}
	if(q->queue == NULL)
	{
		free(q);
		return -1;
	}
	free(q->queue);
	free(q);
	pthread_mutex_destroy(&(q->mutex));
	return 0;
}
int setFinished(waitableQueue q, int threadsNum)
{
	int i;
	if(q == NULL)
	{
		return -1;
	}
	pthread_mutex_lock(&(q->mutex));
	q->fThreads++;
	if(q->fThreads == threadsNum)
	{
		q->finished = 1;
	}
	pthread_mutex_unlock(&(q->mutex));
	return 0;
}
int getFinished(waitableQueue q)
{
	if(q == NULL)
	{
		return -1;
	}
	return (int)(q->finished);
}