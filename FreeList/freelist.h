#ifndef FREELIST_H
#define FREELIST_H

	void* memInit(void* buffer, unsigned int size);
	void* memAlloc(void* buffer, unsigned int size, unsigned int bufferSize);
	int memFree(void** memory, void* buffer, unsigned int bufferSize);	

#endif