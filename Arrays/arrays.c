#include <stdio.h>

int bubbleSort(int* arr, int length)
{
	int smallerCounter;
	int i;
	int temp;
	do
	{
		smallerCounter = 0;
		for(i = 1; i < length; i++)
		{
			if(arr[i] < arr[i - 1])
			{
				temp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = temp;
				smallerCounter++;
			}
		}
	}
	while(smallerCounter > 0);
	return 0;
}

int mergeSort(int* arr, int length, int* sorted)
{
	int i = 0;
	int j = length/2;
	/*int temp;*/
	int s = 0;
	if(length == 1)
	{
		return 0;
	}
	mergeSort(arr + i, length/2, sorted);
	mergeSort(arr + j ,length - length/2, sorted + length/2);
	while(i < length/2 && j < length)
	{
		if(arr[i] > arr[j])
		{
			sorted[s] = arr[j];
			j++;
		}
		else
		{
			sorted[s] = arr[i];
			i++;
		}
		s++;
	}
	while(i < length/2)
	{
		sorted[s] = arr[i];
		i++;
		s++;
	}
	while(j < length)
	{
		sorted[s] = arr[j];
		j++;
		s++;
	}
	for(i = 0; i < length; i++)
	{
		arr[i] = sorted[i];
	}
	return 0;
}
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

int sortEvenOdd(int* arr, int length)
{
	int evencount = 0;
	int i = 0;
	int j = length - 1;
	int temp;
	while(i < j)
	{
		while(arr[i]%2 == 0)
		{
			evencount+=1;
			i++;
		}
		while(arr[j]%2 == 1 || arr[j]%2 == -1)
		{
			j--;
		}
		if(i < j)
		{
			if(arr[j]%2 == 0)
			{
				evencount++;
			}
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	}
	return evencount;
}

int mostCommon(int* arr, int length)
{
	int mostcommon = arr[0];
	int mostcommoncount = 1;
	int i = 1;
	int j;
	int currentcount = 1;
	for(j = 1; j < length; j++)
	{
		if(arr[j] == mostcommon)
		{
			mostcommoncount+=1;
		}
	}
	for(i = 1; i < length; i++)
	{
		if(arr[i] == arr[i - 1] || arr[i] == mostcommon)
		{
			i++;
		}
		currentcount = 1;
		for(j = i + 1; j < length; j++)
		{
			if(arr[j] == arr[i])
			{
				currentcount ++;
			}
		}
		if(currentcount > mostcommoncount)
		{
			mostcommoncount = currentcount;
			mostcommon = arr[i];
		}
	}
	return mostcommon;
}

int main()
{
	int even = 0;
	int arr0[] = {5, 8, 4, 0, 3, 1, 5, 2, 6, 7};
	int arr1[] = {5, 8, 4, 0, 3, 1, 5, 2, 6, 7};
	int sorted[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int i;
	int arr[] = {1, 0, 1, 0, 1, 1, 0, 0, 1, 0};
	int lengthVal;
	int evenOdd[100];
	int mostCom[100];
	int arr2[] = {3, 6, 8, 3, 9, 12, 45, 9};
	int arr3[] = {3, 6, 8, 3, 9, 12, 45, 9, 12, 56, 12};
	mergeSort(arr0, 10, sorted);
	bubbleSort(arr1, 10);
	sortZeroOne(arr);
	printf("Merge sorted 5 8 4 0 3 1 5 2 6 7:\n");
	for(i = 0; i < 10; i++)
	{
		printf("%d ", arr0[i]);
	}
	putchar('\n');
	printf("Bubble sorted 5 8 4 0 3 1 5 2 6 7:\n");
	for(i = 0; i < 10; i++)
	{
		printf("%d ", arr1[i]);
	}
	putchar('\n');
	putchar('\n');
	printf("Zero one sorted 1 0 1 0 1 1 0 0 1 0:\n");
	for(i = 0; i < 10; i++)
	{
		putchar('0' + arr[i]);
		putchar(' ');
	}
	putchar('\n');
	putchar('\n');
	printf("Choose an array length under 101: ");
	scanf("%d", &lengthVal);
	putchar('\n');
	printf("Enter array objects:\n");
	for(i = 0; i < lengthVal; i++)
	{
		scanf("%d", &evenOdd[i]);
	}
	putchar('\n');
	even = sortEvenOdd(evenOdd, lengthVal);
	printf("Sorted array by even and odd numbers:\n");
	for(i = 0; i < lengthVal; i++)
	{
		printf("%d ", evenOdd[i]);
	}
	putchar('\n');
	printf("Even objects: %d\n\n", even);
	printf("Most common in 3 6 8 3 9 12 45 9: %d\n", mostCommon(arr2, 8));
	printf("Most common in 3 6 8 3 9 12 45 9 12 56 12: %d\n", mostCommon(arr3, 11));
	printf("Choose an array length under 101: ");
	scanf("%d", &lengthVal);
	putchar('\n');
	printf("Enter array objects:\n");
	for(i = 0; i < lengthVal; i++)
	{
		scanf("%d", &mostCom[i]);
	}
	putchar('\n');
	printf("Most common: %d\n", mostCommon(mostCom, lengthVal));
	return 0;
}
