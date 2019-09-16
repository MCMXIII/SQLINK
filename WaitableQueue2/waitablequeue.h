#ifndef WAITABLEQUEUE_H
#define WAITABLEQUEUE_H

	typedef struct waitableQueue* waitableQueue;

	waitableQueue queueCreate(unsigned int size);
	void* readFromQueue(waitableQueue q);
	int writeToQueue(waitableQueue q, void* message);
	unsigned int getAmount(waitableQueue q);
	int destroyQueue(waitableQueue q);
	int setFinished(waitableQueue q, int threadsNum);
	int getFinished(waitableQueue q);
	void broadcastAll(waitableQueue q);
#endif