#include <stdio.h>
#include <stdlib.h>

int* insert(int* arr, int val, int* capacity, int* index)
{
	if(*index < *capacity)
	{
		arr[*index] = val;
		return arr;
	}
	(*capacity)*=2;
	arr = (int*)realloc(arr, (*capacity)*sizeof(int));
	arr[*index] = val;
	return arr;
}

int main()
{
	int arrSize;
	int val = 0;
	int* arr = 0;
	int capacityVariable = 0;
	int* capacity = &capacityVariable;
	int indexVariable = 0;
	int* index = &indexVariable;
	int i;
	printf("Enter an initial array size: ");
	scanf("%d", &arrSize);
	*index = 0;
	*capacity = arrSize;
	arr = (int *)malloc((*capacity)*sizeof(int));
	while(val >= 0)
	{
		printf("Enter a non negative value (or a negative value to terminate): ");
		scanf("%d", &val);
		if(val >= 0)
		{
			arr = insert(arr, val, capacity, index);
			printf("arr[%d] = %d, capacity = %d\n", *index, arr[*index], *capacity);
			(*index)++;
		}
	}
	for(i = 0; i < *index; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	free(arr);
	return 0;
}
