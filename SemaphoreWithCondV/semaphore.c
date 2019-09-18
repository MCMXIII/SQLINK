#include <pthread.h>
#include <stdio.h>

int x = 0;
typedef struct
{
	int value;
	int size;
	pthread_cond_t condv;
	pthread_mutex_t mutex;
} condSemaphore;
condSemaphore conds;

void seminit(condSemaphore* sem, int size)
{
	sem->value = 0;
	sem->size = size;
	pthread_cond_init(&(sem->condv), NULL);
	pthread_mutex_init(&(sem->mutex), NULL);
}

void sempost(condSemaphore* s)
{
	pthread_mutex_lock(&(s->mutex));
	while(s->value == 0)
	{
		pthread_cond_wait(&(s->condv), &(s->mutex));
	}
	s->value--;
	pthread_mutex_unlock(&(s->mutex));
	pthread_cond_signal(&(s->condv));
}

void semwait(condSemaphore* s)
{
	pthread_mutex_lock(&(s->mutex));
	while(s->value == s->size)
	{
		pthread_cond_wait(&(s->condv), &(s->mutex));
	}
	s->value++;
	pthread_mutex_unlock(&(s->mutex));
	pthread_cond_signal(&(s->condv));
}
void* increase(void* number)
{
	semwait(&conds);
	printf("%d\n", *((int*)number));
	sleep(1);
	sempost(&conds);
}
int main()
{
	pthread_t threads[10];
	int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int i = 0;
	seminit(&conds, 2);
	for(i = 0; i < 10; i++)
	{
		pthread_create(&(threads[i]), NULL, &increase, (void*)(&(arr[i])));
	}
	for(i = 0; i < 10; i++)
	{
		pthread_join(threads[i], NULL);
	}
}