#include "memPage_t.h"
#include "memPool_t.h"
#include <stdio.h>
#include <string.h>

int main()
{
	char string[150];
	memPool_t page(7);
	int action = -1;
	int i;
	unsigned int index;
	unsigned int bytes;
	while(action != 0)
	{
		printf("1 to write a string into memory, 2 to write a string into a specific index, 3 to read a string from memory, 4 to read a string from a specific index, 5 to write an unsigned int into memory, 6 to write an unsigned int into a specific index, 7 to read an unsigned int from memory, 8 to read an unsigned int from a specific index, 9 to get capacity, 10 to set capacity, 0 to exit.\n");
		scanf("%d", &action);
		for(i = 0; i < 150; i++)
		{
			string[i] = 0;
		}
		switch(action)
		{
			case 1:
				printf("Enter a string:\n");
				scanf("%s", string);
				page.write((void*)string, strlen(string));
				break;
			case 2:
				printf("Enter a string:\n");
				scanf("%s", string);
				printf("Enter an index:\n");
				scanf("%u", &index);
				page.write(index, (void*)string, strlen(string));
				break;
			case 3:
				printf("Enter a size to read:\n");
				scanf("%u", &bytes);
				page.read((void*)string, bytes);
				printf("%s\n", string);
				break;
			case 4:
				printf("Enter a size to read:\n");
				scanf("%u", &bytes);
				printf("Enter an index:\n");
				scanf("%u", &index);
				page.read((void*)string, index, bytes);
				printf("%s\n", string);
				break;
			case 5:
				printf("Enter a non negative int:\n");
				scanf("%u", &bytes);
				page.write((void*)&bytes, sizeof(unsigned int));
				break;
			case 6:
				printf("Enter a non negative int:\n");
				scanf("%u", &bytes);
				printf("Enter an index:\n");
				scanf("%u", &index);
				page.write(index, (void*)&bytes, sizeof(unsigned int));
				break;
			case 7:
				page.read((void*)&bytes, sizeof(unsigned int));
				printf("%u\n", bytes);
				break;
			case 8:
				printf("Enter an index:\n");
				scanf("%u", &index);
				page.read((void*)&bytes, index, sizeof(unsigned int));
				printf("%u\n", bytes);
				break;
			case 9:
				printf("%u\n", page.getCapacity());
				break;
			case 10:
				printf("Enter a new capacity:\n");
				scanf("%u", &bytes);
				page.setCapacity(bytes);
				break;
			default:
				break;
		}
	}
}