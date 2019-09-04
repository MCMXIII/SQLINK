#include "freelist.h"
#include <stdint.h>

#define LEFT_BIT (1<<31)
#define ALLOC_BIT(x) (x + LEFT_BIT)
#define FREE_BIT(x) (x - LEFT_BIT)

void splitSpace(void** ptr, void** ptr2, unsigned int size)
{
	if(**((unsigned int**)ptr) > size)
	{
		*ptr2 = (void*)((unsigned char*)(*ptr) + size + 4);
		**((unsigned int**)ptr2) = (**((unsigned int**)ptr) - size - 4);
		**((unsigned int**)ptr) = size;
	}
	**((unsigned int**)ptr) = ALLOC_BIT(**((unsigned int**)ptr));
}
void* memInit(void* buffer, unsigned int size)
{
	unsigned int* ptr = (unsigned int*)buffer;
	int i;
	for(i = 0; i < size; i++)
	{
		*(ptr) = 0;
		ptr++;
	}
	size <<= 2;
	if(buffer == 0 || size <= 4 || size & LEFT_BIT != 0)
	{
		return 0;
	}
	while((intptr_t)buffer & 3 != 0)
	{
	
		buffer = (void*)((char*)buffer+1);
		size--;
	}
	while(size & 3 != 0)
	{
		size--;
	}
	*((unsigned int*)buffer) = size - 4;
	return buffer;
}
void* memAlloc(void* buffer, unsigned int size, unsigned int bufferSize)
{
	void* ptr = buffer;
	void* ptr2;
	size <<= 2;
	bufferSize <<= 2;
	if(buffer == 0 || size < 4 || size & LEFT_BIT != 0)
	{
		return 0;
	}
	while((char *)(ptr) - (char*)(buffer) < bufferSize)
	{
		if((*((unsigned int*)ptr)&LEFT_BIT)<=0)
		{
			if(*((unsigned int*)ptr) >= size)
			{
				splitSpace(&ptr, &ptr2, size);
				return ptr;
			}
			if(((char *)(ptr) - (char*)(buffer))+*((unsigned int*)ptr) + 4 >= bufferSize)
			{
				return 0;
			}
			ptr2 = (void*)((char*)ptr + *((unsigned int*)ptr) + 4);
			while((char *)(ptr2) - (char*)(buffer) < bufferSize && (*((unsigned int*)ptr2)&LEFT_BIT)<=0)
			{
				*((unsigned int*)ptr) += *((unsigned int*)ptr2) + 4;
				if(*((unsigned int*)ptr) >= size)
				{
					splitSpace(&ptr, &ptr2, size);
					return ptr;
				}
				ptr2=(void*)((char*)ptr2 + ((*((unsigned int*)ptr2)) + 4));
			}
			ptr=ptr2;
		}
		else
		{
			ptr=(void*)((char*)ptr+((*((unsigned int*)ptr)-LEFT_BIT) + 4));
		}
	}
	return 0;
}
int memFree(void** memory, void* buffer, unsigned int bufferSize)
{
	void* ptr = *memory;
	bufferSize<<=2;
	if(*memory == 0 || (*((unsigned int*)ptr)&LEFT_BIT)==0)
	{
		return -1;
	}
	ptr=(void*)((char*)ptr+((*((unsigned int*)ptr) -LEFT_BIT + 4)));
	while((char *)(ptr) - (char*)(buffer) < bufferSize && (*((unsigned int*)ptr)&LEFT_BIT)<=0)
	{	
		**((unsigned int**)memory) += *((unsigned int*)ptr) + 4;
		ptr=(void*)((char*)ptr+((*((unsigned int*)ptr) + 4)));
	}
	**((unsigned int**)memory) = FREE_BIT(**((unsigned int**)memory));
	*memory = 0;
	return 0;
}