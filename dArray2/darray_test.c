#include <stdio.h>
#include <string.h>
#include "darray.h"


typedef struct {
	char* name;
	int number;
} footballer;
void destroy(void* _elem, void *context)
{
	if(((footballer*)_elem)->name != NULL)
	{
		free(((footballer*)_elem)->name);
	}
	context = (void*)(&(((footballer*)_elem)->number));
	printf("%d\n", *((int*)context));
	free(_elem);
}
int namecmp(void* _elem1, void* _elem2)
{
	if(((footballer*)_elem1)->name == NULL || ((footballer*)_elem2)->name == NULL)
	{
		return 0;
	}
	return strcmp(((footballer*)_elem1)->name, ((footballer*)_elem2)->name);
}
int numcmp(void* _elem1, void* _elem2)
{
	return ((footballer*)_elem1)->number - ((footballer*)_elem2)->number;
}
int allocFP(footballer** fp)
{

	*fp = (footballer*)malloc(sizeof(footballer));
	if(*fp == NULL)
	{
		return -1;
	}
	(*fp)->name = (char*)malloc(20*sizeof(char));
	if((*fp)->name == NULL)
	{
		return -1;
	}
	return 0;
}
int main()
{
	int size = -1;
	int output = 0;
	int* funcOutput = &output;
	int userInput = 0;
	darray* dArr = 0;
	footballer* fp = 0;
	footballer* replaced = 0;
	char command = 'x';
	while(size < 0)
	{
		printf("Enter a size for a dynamic array!\n");
		scanf("%d", &size);
	}
	darrayCreate(&dArr, size);
	while(command != 'q')
	{
		if(command == 'x')
		{
			printf("a to add, d to delete, g to get, s to set, b to bubble sort, u to quick sort, q to quit.\n");
			command = 'y';
		}
		scanf("%c", &command);
		switch(command)
		{
			case 'a':
			{
				if(allocFP(&fp) == -1)
				{
					command = 'q';
					darrayDestroy(dArr, &destroy, (void*)funcOutput);
					break;
				}
				printf("Enter a name to add!\n");
				scanf("%s", fp->name);
				printf("Enter a number to add!\n");
				scanf("%d", &fp->number);
				darrayAdd(dArr, (void*)fp);
				darrayItemsNum(dArr, funcOutput);
				printf("%d\n", *funcOutput);
				command = 'x';
				break;
			}
			case 'd':
			{
				darrayDelete(dArr, (void**)&fp);
				printf("%d: %s\n", fp->number, fp->name);
				darrayItemsNum(dArr, funcOutput);
				printf("%d\n", *funcOutput);
				command = 'x';
				break;
			}
			case 's':
			{
				printf("Enter an index to set!\n");
				scanf("%d", &userInput);
				darrayItemsNum(dArr, funcOutput);
				if(userInput >= 0 && userInput < *funcOutput)
				{
					if(allocFP(&fp) == -1)
					{
						command = 'q';
						darrayDestroy(dArr, &destroy, (void*)funcOutput);
						break;
					}
					printf("Enter a name to set!\n");
					scanf("%s", fp->name);
					printf("Enter a number to set!\n");
					scanf("%d", &fp->number);
					darraySet(dArr, userInput, (void*)fp, (void**)&replaced);
					printf("%d: %s\n", replaced->number, replaced->name);
				}
				else
				{
					printf("Invalid index!\n");
				}
				command = 'x';
				break;
			}
			case 'g':
			{
				printf("Enter an index to get!\n");
				scanf("%d", &userInput);
				darrayItemsNum(dArr, funcOutput);
				if(userInput >= 0 && userInput < *funcOutput)
				{
					darrayGet(dArr, userInput, (void**)(&fp));
					printf("%d: %s\n", fp->number, fp->name);
				}
				else
				{
					printf("Invalid index!\n");
				}
				command = 'x';
				break;
			}
			case 'b':
			{
				darraySort(dArr, &numcmp);
				command = 'x';
				break;
			}
			case 'u':
			{
				darrayItemsNum(dArr, funcOutput);
				darrayQuickSort(dArr, &namecmp, 0, (*funcOutput) - 1);
				command = 'x';
				break;
			}
			case 'q':
			{
				darrayDestroy(dArr, &destroy, (void*)funcOutput);
				break;
			}
			default:
			{
			}
		}
	}
	return 0;
}
