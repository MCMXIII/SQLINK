#include "waitablequeue.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

typedef struct {
	waitableQueue pTC;
	waitableQueue cTP;
	int amount;
	char* message;
} argsStruct;
void* producer(void* arg)
{
	char* msg;
	int x = (rand()%100) + 1;
	int i = 0;
	for(i = 0; i < x; i++)
	{
		printf("Producer enters message: %s", ((argsStruct*)arg)->message);
		writeToQueue(((argsStruct*)arg)->pTC, (void*)(((argsStruct*)arg)->message));
	}
	setFinished(((argsStruct*)arg)->pTC, ((argsStruct*)arg)->amount);
	i = 0;
	while((getAmount(((argsStruct*)arg)->cTP) > 0 || !getFinished(((argsStruct*)arg)->cTP))&&i < x)
	{
		msg = (char*)(readFromQueue(((argsStruct*)arg)->cTP));
		if(msg != NULL)
		{
			printf("	Message read by producer: %s", msg);
			i++;
		}
	}
	broadcastAll(((argsStruct*)arg)->cTP);
	broadcastAll(((argsStruct*)arg)->pTC);
	return NULL;
}

void* consumer(void* arg)
{
	int acknowledgements = 0, i = 0;
	char* msg;
	msg = (char*)(readFromQueue(((argsStruct*)arg)->pTC));
	while(msg != NULL)
	{
		printf("	Message read by consumer: %s", msg);
		msg = (char*)(readFromQueue(((argsStruct*)arg)->pTC));
		acknowledgements++;
	}
	for(i = 0; i < acknowledgements; i++)
	{
		printf("Consumer enters message: %s", ((argsStruct*)arg)->message);
		writeToQueue(((argsStruct*)arg)->cTP, (void*)(((argsStruct*)arg)->message));
	}
	setFinished(((argsStruct*)arg)->cTP, ((argsStruct*)arg)->amount);
	broadcastAll(((argsStruct*)arg)->cTP);
	broadcastAll(((argsStruct*)arg)->pTC);
	return NULL;
}

pthread_t* create(int size, waitableQueue pTC, waitableQueue cTP, argsStruct*** args, unsigned int isProducers)
{
	pthread_t* arr;
	argsStruct* a;
	int i;
	arr = (pthread_t*)malloc(size*sizeof(pthread_t));
	if(arr == NULL)
	{
		return;
	}
	*args = (argsStruct**)malloc(size*sizeof(argsStruct*));
	if(args == NULL)
	{
		free(arr);
		return;
	}
	for(i = 0; i < size; i++)
	{
		a = (argsStruct*)malloc(sizeof(argsStruct));
		if(a == NULL)
		{
			free(args);
			free(arr);
			return;
		}
		a->amount = size;
		a->pTC = pTC;
		a->cTP = cTP;
		a->message = (char*)malloc(25*sizeof(char));
		if(a->message == NULL)
		{
			free(args);
			free(arr);
			free(a);
			return;
		}
		if(isProducers)
		{
			sprintf(a->message, "Out message number %d\n", i);
			pthread_create(&(arr[i]), NULL, &producer, (void*)a);
		}
		else
		{
			sprintf(a->message, "In message number %d\n", i);
			pthread_create(&(arr[i]), NULL, &consumer, (void*)a);
		}
		(*args)[i] = a;
	}
	return arr;
}
void destroy(pthread_t* arr, argsStruct** args)
{
	int i;
	int amount = 0;
	if(arr != NULL)
	{
		free(arr);
	}
	if(args != NULL)
	{
		if(args[0] != NULL)
		{
			amount = args[0]->amount;
		}
		for(i = 0; i < amount; i++)
		{
			if(args[i] != NULL)
			{
				if(args[i]->message != NULL)
				{
					free(args[i]->message);
				}
				free(args[i]);
			}
		}
		free(args);
	}
}
int main()
{
	int i;
	waitableQueue producerToConsumer;
	waitableQueue consumerToProducer;
	pthread_t* producers;
	pthread_t* consumers;
	argsStruct** producersArgs;
	argsStruct** consumersArgs;
	srand(time(0));
	producerToConsumer = queueCreate(10);
	if(producerToConsumer == NULL)
	{
		return -1;
	}
	consumerToProducer = queueCreate(10);
	if(consumerToProducer == NULL)
	{
		destroyQueue(producerToConsumer);
		return -1;
	}
	producers = create(200, producerToConsumer, consumerToProducer, &producersArgs, 1);
	if(producers == NULL)
	{
		destroyQueue(producerToConsumer);
		destroyQueue(consumerToProducer);
		return -1;
	}
	consumers = create(300, producerToConsumer, consumerToProducer, &consumersArgs, 0);
	if(consumers == NULL)
	{
		destroyQueue(producerToConsumer);
		destroyQueue(consumerToProducer);
		destroy(producers, producersArgs);
		return -1;
	}
	for(i = 0; i < 200; i++)
	{
		pthread_join(producers[i], NULL);
	}
	for(i = 0; i < 300; i++)
	{
		pthread_join(consumers[i], NULL);
	}
	destroy(producers, producersArgs);
	destroy(consumers, consumersArgs);
	destroyQueue(producerToConsumer);
	destroyQueue(consumerToProducer);
	printf("Done!\n");
	return 0;
}