#include <semaphore.h>
#include <stdio.h>
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
	/*pthread_cond_t full;
	pthread_cond_t empty;*/
	pthread_cond_t cond;
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
	/*pthread_cond_init(&(q->full), NULL);
	pthread_cond_init(&(q->empty), NULL);*/
	pthread_cond_init(&(q->cond), NULL);
	/*for(i = 0; i < size; i++)
	{
		sem_wait(&(q->empty));
		q->queue[i] = NULL;
	}*/
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
	if(q->amount > 0)
	{
		pthread_mutex_lock(&(q->mutex));
	}
	while(q->amount == 0)
	{
		printf("pre read waiting: %u\n", q->amount);
		if(q->amount == 0 && q->finished == 1)
		{
			return NULL;
		}
		if(q->amount > 0)
		{
			printf("amount: %u\n", q->amount);
			pthread_mutex_lock(&(q->mutex));
			break;
		}
		pthread_cond_wait(&(q->cond), &(q->mutex));
	}
	
	/*while(q->amount == 0)
	{
		printf("read waiting: %u\n", q->amount);
		if(q->amount == 0 && q->finished == 1)
		{
			return NULL;
		}
		pthread_cond_wait(&(q->cond), &(q->mutex));
	}*/
	/*printf("first: %u\n", q->amount);
	pthread_mutex_lock(&(q->mutex));
	printf("first after lock: %u\n", q->amount);*/
	message = q->queue[0];
	for(i = 0; i < q->amount; i++)
	{
		q->queue[i] = q->queue[i + 1];
	}
	/*printf("second: %u\n", q->amount);*/
	q->queue[--q->amount] = NULL;
	/*printf("third: %u\n", q->amount);*/
	pthread_cond_signal(&(q->cond));
	pthread_mutex_unlock(&(q->mutex));
	return message;
}
int writeToQueue(waitableQueue q, void* message)
{
	if(q == NULL || q->queue == NULL)
	{
		return -1;
	}
	if(q->amount < q->size)
	{
		pthread_mutex_lock(&(q->mutex));
	}
	while(q->amount == q->size)
	{
		printf("pre write waiting: %u\n", q->amount);
		if(q->amount < q->size)
		{
			pthread_mutex_lock(&(q->mutex));
			break;
		}
		pthread_cond_wait(&(q->cond), &(q->mutex));
	}
	/*pthread_mutex_lock(&(q->mutex));*/
	while(q->amount == q->size)
	{
		printf("write waiting: %u\n", q->amount);
		pthread_cond_wait(&(q->cond), &(q->mutex));
	}
	/*pthread_mutex_lock(&(q->mutex));*/
	q->queue[q->amount++] = message;
	q->started = 1;
	pthread_cond_signal(&(q->cond));
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
		printf("Finished!\n");
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