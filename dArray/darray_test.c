#include <stdio.h>
#include "darray.h"

int main()
{
	int size = -1;
	int output = 0;
	int* funcOutput = &output;
	int userInput = 0;
	int userInput2 = 0;
	darray* dArr = 0;
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
			printf("a to add, d to delete, g to get, s to set, b to bubble sort, q to quit.\n");
			command = 'y';
		}
		scanf("%c", &command);
		switch(command)
		{
			case 'a':
			{
				printf("Enter a number to add!\n");
				scanf("%d", &userInput);
				darrayAdd(dArr, userInput);
				darrayItemsNum(dArr, funcOutput);
				printf("%d\n", *funcOutput);
				command = 'x';
				break;
			}
			case 'd':
			{
				darrayDelete(dArr, funcOutput);
				printf("%d\n", *funcOutput);
				darrayItemsNum(dArr, funcOutput);
				printf("%d\n", *funcOutput);
				command = 'x';
				break;
			}
			case 's':
			{
				printf("Enter an index to set!\n");
				scanf("%d", &userInput);
				printf("Enter a number to set!\n");
				scanf("%d", &userInput2);
				darraySet(dArr, userInput, userInput2);
				command = 'x';
				break;
			}
			case 'g':
			{
				printf("Enter an index to get!\n");
				scanf("%d", &userInput);
				darrayGet(dArr, userInput, funcOutput);
				printf("%d\n", *funcOutput);
				command = 'x';
				break;
			}
			case 'b':
			{
				darraySort(dArr, 0);
				command = 'x';
				break;
			}
			case 'q':
			{
				break;
			}
			default:
			{
			}
		}
	}
	return 0;
}
