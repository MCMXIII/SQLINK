#include <stdio.h>
#include "bitmap.h"

int main()
{
	Bitmap * b;
	int action = 0, index = 0, size = 0;
	int (*funcs[4])(Bitmap*, int);
	while(size <= 0)
	{
		printf("Enter a Bitmap size:\n");
		scanf("%d", &size);
		if(size > 0)
		{
			b = createBitmap(size);
			if(b == NULL)
			{
				return -1;
			}

		}
	}
	funcs[0] = &turnOn;
	funcs[1] = &turnOff;
	funcs[2] = &changeBit;
	funcs[3] = &bitStatus;
	while(action != 5)
	{
		printf("Enter a command and a bit index under your chosen size with one blank space between them.\n1 - turn on a bit, 2 - turn off a bit, 3 - change a bit, 4 - get the bit's current status, 5 - quit.\n");
		scanf("%d %d", &action, &index);
		if(action >= 1 && action <= 4)
		{
			printf("Function activated. result is %d.\n", (*(funcs[action - 1]))(b, index));
			printBitmap(b);
			printBitmap2(b);
		}
	}
	destroyBitmap(b);
	return 0;
}
