#include "waitablequeue.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

int messageID;
waitableQueue producerToConsumer;
waitableQueue consumerToProducer;
int producersAmount = 0;
int consumersAmount = 0;
char** outMessages;
char** inMessages;

void* producer(void* arg)
{
	char* msg;
	int x = (rand()%10) + 1;
	int i = 0;
	for(i = 0; i < x; i++)
	{
		printf("Producer enters message: %s", (char*)arg);
		writeToQueue(producerToConsumer, arg);		
	}
	setFinished(producerToConsumer, 20);
	while(getAmount(consumerToProducer) > 0 || !getFinished(consumerToProducer))
	{
		msg = (char*)(readFromQueue(consumerToProducer));
		if(msg != NULL)
		{
			printf("	Message read by producer: %s", msg);
		}
	}
	return NULL;
}

void* consumer(void* arg)
{
	char* msg;
	while(getAmount(producerToConsumer) > 0 || !getFinished(producerToConsumer))
	{
		msg = (char*)(readFromQueue(producerToConsumer));
		if(msg != NULL)
		{
			printf("	Message read by consumer: %s", msg);
		}
		printf("Consumer enters message: %s", (char*)arg);
		writeToQueue(consumerToProducer, arg);
	}
	setFinished(consumerToProducer, 15);
	return NULL;
}

pthread_t* createProducers(int size)
{
	pthread_t* arr;
	int i;
	producersAmount = size;
	arr = (pthread_t*)malloc(size*sizeof(pthread_t));
	if(arr == NULL)
	{
		return;
	}
	outMessages = (char**)malloc(size*sizeof(char*));
	if(outMessages == NULL)
	{
		free(arr);
		return;
	}
	for(i = 0; i < size; i++)
	{
		outMessages[i] = (char*)malloc(25*sizeof(char));
		if(outMessages[i] == NULL)
		{
			free(arr);
			free(outMessages);
			return;
		}
		sprintf(outMessages[i], "Out message number %d\n", i);
	}
	for(i = 0; i < size; i++)
	{
		pthread_create(&(arr[i]), NULL, &producer, (void*)(outMessages[i]));
	}
	return arr;
}
pthread_t* createConsumers(int size)
{
	pthread_t* arr;
	int i;
	consumersAmount = size;
	arr = (pthread_t*)malloc(size*sizeof(pthread_t));
	if(arr == NULL)
	{
		return;
	}
	inMessages = (char**)malloc(size*sizeof(char*));
	if(inMessages == NULL)
	{
		free(arr);
		return;
	}
	for(i = 0; i < size; i++)
	{
		inMessages[i] = (char*)malloc(25*sizeof(char));
		if(inMessages[i] == NULL)
		{
			free(arr);
			free(inMessages);
			return;
		}
		sprintf(inMessages[i], "In message number %d\n", i);
	}
	for(i = 0; i < size; i++)
	{
		pthread_create(&(arr[i]), NULL, &consumer, (void*)(inMessages[i]));
	}
	return arr;
}
void destroyProducers(pthread_t* arr)
{
	int i;
	if(arr != NULL)
	{
		free(arr);
	}
	if(outMessages != NULL)
	{
		for(i = 0; i < producersAmount; i++)
		{
			if(outMessages[i] != NULL)
			{
				free(outMessages[i]);
			}
		}
		free(outMessages);
	}
}
void destroyConsumers(pthread_t* arr)
{
	int i;
	if(arr != NULL)
	{
		free(arr);
	}
	if(inMessages != NULL)
	{
		for(i = 0; i < consumersAmount; i++)
		{
			if(inMessages[i] != NULL)
			{
				free(inMessages[i]);
			}
		}
		free(inMessages);
	}
}
int main()
{
	int i;
	pthread_t* producers;
	pthread_t* consumers;
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
	producers = createProducers(20);
	if(producers == NULL)
	{
		destroyQueue(producerToConsumer);
		destroyQueue(consumerToProducer);
		return -1;
	}
	consumers = createConsumers(15);
	if(consumers == NULL)
	{
		destroyQueue(producerToConsumer);
		destroyQueue(consumerToProducer);
		destroyProducers(producers);
		return -1;
	}
	for(i = 0; i < producersAmount; i++)
	{
		pthread_join(producers[i], NULL);
	}
	for(i = 0; i < consumersAmount; i++)
	{
		pthread_join(consumers[i], NULL);
	}
	destroyProducers(producers);
	destroyConsumers(consumers);
	destroyQueue(producerToConsumer);
	destroyQueue(consumerToProducer);
	printf("Done!\n");
	return 0;
}