#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "waitablequeue.h"

struct waitableQueue {
	void** queue;
	unsigned int amount;
	unsigned int size;
	unsigned int started;	
	unsigned int finished;
	int fThreads;
	pthread_cond_t condR;
	pthread_cond_t condW;
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
	q->size = size;
	q->started = 0;	
	q->finished = 0;
	q->fThreads = 0;
	pthread_cond_init(&(q->condR), NULL);
	pthread_cond_init(&(q->condW), NULL);
	for(i = 0; i < size; i++)
	{
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
	pthread_mutex_lock(&(q->mutex));
	while(q->amount == 0)
	{
		if(q->amount == 0 && q->finished == 1)
		{
			pthread_mutex_unlock(&(q->mutex));
			return NULL;
		}
		pthread_cond_broadcast(&(q->condW));
		pthread_cond_wait(&(q->condR), &(q->mutex));
	}
	message = q->queue[0];
	for(i = 0; i < q->amount; i++)
	{
		q->queue[i] = q->queue[i + 1];
	}
	q->queue[--q->amount] = NULL;
	pthread_mutex_unlock(&(q->mutex));
	pthread_cond_broadcast(&(q->condW));
	return message;
}
int writeToQueue(waitableQueue q, void* message)
{
	if(q == NULL || q->queue == NULL)
	{
		return -1;
	}
	pthread_mutex_lock(&(q->mutex));
	while(q->amount == q->size)
	{
		pthread_cond_broadcast(&(q->condR));
		pthread_cond_wait(&(q->condW), &(q->mutex));
	}
	q->queue[q->amount++] = message;
	q->started = 1;
	pthread_mutex_unlock(&(q->mutex));
	pthread_cond_broadcast(&(q->condR));
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
	pthread_cond_broadcast(&(q->condR));
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
void broadcastAll(waitableQueue q)
{
	if(q == NULL)
	{
		return;
	}
	pthread_cond_broadcast(&(q->condR));
	pthread_cond_broadcast(&(q->condW));
}