#include <stdio.h>

int sortZeroOne(int* arr)
{
	int i = 0;
	int j = 0;
	while(arr[j+1] == 0 || arr[j+1] == 1)
	{
		j++;
	}
	while(i < j)
	{
		while(arr[i] == 0)
		{
			i++;
		}
		while(arr[j] == 1)
		{
			j--;
		}
		if(i < j)
		{
			arr[i] = 0;
			arr[j] = 1;
			i++;
			j--;
		}
	}
	return 0;
}

int main()
{
	int i;
	int arr[] = {1, 0, 1, 0, 1, 1, 0, 0, 1, 0};
	sortZeroOne(arr);
	for(i = 0; i < 10; i++)
	{
		putchar('0' + arr[i]);
		putchar(' ');
	}
	putchar('\n');
	return 0;
}
