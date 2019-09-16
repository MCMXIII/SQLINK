#include "waitablequeue.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

typedef struct {
	waitableQueue* pTC;
	waitableQueue* cTP;
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
		while(writeToQueue(((argsStruct*)arg)->pTC, (void*)(((argsStruct*)arg)->message) == -1){}
	}
	setFinished(((argsStruct*)arg)->pTC, ((argsStruct*)arg)->amount);
	i = 0;
	while((getAmount(writeToQueue(((argsStruct*)arg)->cTP) > 0 || !getFinished(writeToQueue(((argsStruct*)arg)->cTP))&&i < x)
	{
		msg = (char*)(readFromQueue(((argsStruct*)arg)->cTP));
		if(msg != NULL)
		{
			printf("	Message read by producer: %s", msg);
			i++;
		}
	}
	free(arg);
	return NULL;
}

void* consumer(void* arg)
{
	char* msg;
	msg = (char*)(readFromQueue(((argsStruct*)arg)->pTC));
	while(msg != NULL)
	{
		printf("	Message read by consumer: %s", msg);
		printf("Consumer enters message: %s", ((argsStruct*)arg)->message);
		writeToQueue(((argsStruct*)arg)->cTP, (void*)(((argsStruct*)arg)->message));
		msg = (char*)(readFromQueue(((argsStruct*)arg)->pTC));
	}
	setFinished(((argsStruct*)arg)->cTP, ((argsStruct*)arg)->amount);
	free(arg);
	return NULL;
}

pthread_t* create(int size, waitableQueue* pTC, waitableQueue* cTP, char** messages, unsigned int isProducers)
{
	pthread_t* arr;
	argsStruct* a;
	int i;
	arr = (pthread_t*)malloc(size*sizeof(pthread_t));
	if(arr == NULL)
	{
		return;
	}
	for(i = 0; i < size; i++)
	{
		messages = (char**)malloc(size*sizeof(char*));
		if(messages == NULL)
		{
			free(messages);
			return;
		}
		a = (argsStruct*)malloc(sizeof(argsStruct));
		if(a == NULL)
		{
			free(messages);
			free(arr);
			return;
		}
		a->amount = size;
		a->pTC = pTC;
		a->cTP = cTP;
		a->message = (char*)malloc(25*sizeof(char));
		if(a->message == NULL)
		{
			free(messages);
			free(arr);
			free(a);
			return;
		}
		if(isProducers)
		{
			sprintf(a->message, "Out message number %d\n", i);
		}
		else
		{
			sprintf(a->message, "In message number %d\n", i);
		}
		messages[i] = a->message;
		pthread_create(&(arr[i]), NULL, &producer, (void*)a);
	}
	return arr;
}

void destroy(pthread_t* arr, char** messages, int amount)
{
	int i;
	if(arr != NULL)
	{
		free(arr);
	}
	if(messages != NULL)
	{
		for(i = 0; i < amount; i++)
		{
			if(messages[i] != NULL)
			{
				free(messages[i]);
			}
		}
		free(messages);
	}
}
int main()
{
	int i;
	waitableQueue producerToConsumer;
	waitableQueue consumerToProducer;
	argsStruct prod;
	argsStruct cons;
	char** outMessages;
	char** inMessages;
	prod.amount = 0;
	cons.amount = 0;
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
	prod.pTC = producerToConsumer;
	cons.pTC = producerToConsumer;
	prod.cTP = consumerToProducer;
	cons.cTP = consumerToProducer;
	producers = create(200, producerToConsumer, consumerToProducer, outMessages, 1);
	if(producers == NULL)
	{
		destroyQueue(producerToConsumer);
		destroyQueue(consumerToProducer);
		return -1;
	}
	consumers = create(300, producerToConsumer, consumerToProducer, inMessages, 0);
	if(consumers == NULL)
	{
		destroyQueue(producerToConsumer);
		destroyQueue(consumerToProducer);
		destroy(producers, outMessages, 300);
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
	destroy(producers, outMessages, 300);
	destroy(consumers, inMessages, 200);
	destroyQueue(producerToConsumer);
	destroyQueue(consumerToProducer);
	printf("Done!\n");
	return 0;
}