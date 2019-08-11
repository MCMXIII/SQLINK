#include "dynamicarray.h"

struct dArr{
	int* arr;
	int capacity;
	int index;
};
dArray create(int capacity)
{
	dArray array = (dArray)malloc(sizeof(struct dArr));
	array->capacity = capacity;
	array->arr = (int *)malloc(capacity*sizeof(int));
	array->index = 0;
	if (array->arr == NULL)
	{
		printf("Error! Cannot create an array.\n");
	}
	return array;
}
dArray insert(dArray array, int val)
{
	int* temp;
	if(array == NULL)
	{
		printf("Error! Cannot insert %d.\n", val);
		return array;
	}
	temp = array->arr;
	if(array->index < array->capacity)
	{
		array->arr[(array->index)++] = val;
		printf("arr[%d] = %d, capacity = %d\n", (array->index - 1), array->arr[(array->index) - 1], array->capacity);
		return array;
	}
	array->arr = (int*)realloc(array->arr, (2*(array->capacity))*sizeof(int));
	if(array->arr == NULL)
	{
		printf("Error! Cannot insert %d.\n", val);
		return array;
	}
	if(array->arr != temp)
	{
		free(array->arr);
		array->arr = temp;
	}
	array->arr[(array->index)++] = val;
	(array->capacity)*=2;
	printf("arr[%d] = %d, capacity = %d\n", (array->index - 1), array->arr[(array->index) - 1], array->capacity);
	return array;
}
dArray arrprint(dArray arr)
{
	int i;
	if(arr == NULL || arr->index == 0)
	{
		printf("No items to print!\n");
		return arr;
	}
	for(i = 0; i < arr->index; i++)
	{
		printf("%d ", arr->arr[i]);
	}
	printf("\n");
	return arr;
}
dArray destroy(dArray arr)
{
	if(arr != NULL)
	{
		free(arr->arr);
	}
	free(arr);
	return arr;
}
