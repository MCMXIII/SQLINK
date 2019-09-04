#include "freelist.h"
#include <stdlib.h>
#include <stdio.h>

void printAddressValue(void* buffer, unsigned int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		printf("%u %p\n", *((unsigned int*)buffer), buffer);	
		buffer = (unsigned int*)buffer + 1;
	}
}
int main()
{
	void* buffer = malloc(50*sizeof(unsigned int));
	void* ptr = buffer;
	void* space1;
	void* space2;
	void* space3;
	void* space4;
	void* space5;
	buffer = memInit(buffer, 50);
	printf("%u\n", *((unsigned int*)buffer));
	space1 = memAlloc(buffer, 10, 50);
	space2 = memAlloc(buffer, 10, 50);
	space3 = memAlloc(buffer, 20, 50);
	printf("%p %p %p\n", space1, space2, space3);
	printf("%u %u %u\n", *((unsigned int*)space1), *((unsigned int*)space2), *((unsigned int*)space3));
	/*printAddressValue(buffer, 50);	
	printf("Not freed!\n\n");*/
	memFree(&space2, buffer, 50);
	/*printf("Freed!\n\n");
	printAddressValue(buffer, 50);*/
	space4 = memAlloc(buffer, 5, 50);
	space5 = memAlloc(buffer, 30, 50);
	printf("%p %p %p %p %p\n", space1, space2, space3, space4, space5);
	printf("%u %u %u\n", *((unsigned int*)space1), *((unsigned int*)space3), *((unsigned int*)space4)/*, *((unsigned int*)space4), *((unsigned int*)space5)*/);
	space5 = memAlloc(buffer, 3, 50);
	printf("%p %p %p %p %p\n", space1, space2, space3, space4, space5);
	printf("%u %u %u %u\n", *((unsigned int*)space1), *((unsigned int*)space3), *((unsigned int*)space4), *((unsigned int*)space5)/*, *((unsigned int*)space4), *((unsigned int*)space5)*/);
	memFree(&space4, buffer, 50);
	memFree(&space5, buffer, 50);
	space4 = memAlloc(buffer, 7, 50);
	printf("%p %p %p %p %p\n", space1, space2, space3, space4, space5);
	printf("%u %u %u\n", *((unsigned int*)space1), *((unsigned int*)space3), *((unsigned int*)space4)/*, *((unsigned int*)space4), *((unsigned int*)space5)*/);
	memFree(&space4, buffer, 50);
	memFree(&space3, buffer, 50);
	memFree(&space1, buffer, 50);
	free((void*)((unsigned int*)buffer - 1));
	return 0;
}