#include "dynamicparray.h"

struct dArr{
	int** arr;
	int capacity;
	int index;
};
dArray create(int capacity)
{
	dArray array = (dArray)malloc(sizeof(struct dArr));
	if (array == NULL)
	{
		printf("Error! Cannot create an array.\n");
		return array;
	}
	array->capacity = capacity;
	array->arr = (int **)malloc(capacity*sizeof(int*));
	if (array->arr == NULL)
	{
		printf("Error! Cannot create an array.\n");
		return NULL;
	}
	array->index = 0;
	return array;
}
dArray insert(dArray array, int* valp)
{
	int** temp;
	if(array == NULL)
	{
		printf("Error! Cannot insert pointer to %d.\n", *valp);
		return array;
	}
	temp = array->arr;
	if(array->index < array->capacity)
	{
		array->arr[(array->index)++] = valp;
		printf("arr[%d] = pointer to %d, capacity = %d\n", (array->index - 1), *(array->arr[(array->index) - 1]), array->capacity);
		return array;
	}
	array->arr = (int**)realloc(array->arr, (2*(array->capacity))*sizeof(int*));
	if(array->arr == NULL)
	{
		printf("Error! Cannot insert pointer to %d.\n", *valp);
		return array;
	}
	/*if(array->arr != temp)
	{
		if(temp != NULL)
		{
			free(temp);
		}
	}*/
	array->arr[(array->index)++] = valp;
	(array->capacity)*=2;
	printf("arr[%d] = pointer to %d, capacity = %d\n", (array->index - 1), *(array->arr[(array->index) - 1]), array->capacity);
	return array;
}
/*dArray insertInt(dArray array, int val)
{
	int** temp;
	int* ptr;
	if(array == NULL)
	{
		printf("Error! Cannot insert pointer to %d.\n", val);
		return array;
	}
	ptr = (int *)malloc(sizeof(int));
	if(ptr == NULL)
	{
		printf("Error! Cannot insert pointer to %d.\n", val);
		return array;
	}
	*ptr = val;
	temp = array->arr;
	if(array->index < array->capacity)
	{
		array->arr[(array->index)++] = ptr;
		printf("arr[%d] = pointer to %d, capacity = %d\n", (array->index - 1), *(array->arr[(array->index) - 1]), array->capacity);
		return array;
	}
	array->arr = (int**)realloc(array->arr, (2*(array->capacity))*sizeof(int*));
	if(array->arr == NULL)
	{
		printf("Error! Cannot insert pointer to %d.\n", val);
		return array;
	}
	if(array->arr != temp)
	{
		free(array->arr);
		array->arr = temp;
	}
	array->arr[(array->index)++] = ptr;
	(array->capacity)*=2;
	printf("arr[%d] = pointer to %d, capacity = %d\n", (array->index - 1), *(array->arr[(array->index) - 1]), array->capacity);
	return array;
}*/
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
		printf("%d ", *(arr->arr[i]));
	}
	printf("\n");
	return arr;
}
dArray destroy(dArray arr)
{
	if(arr != NULL)
	{
		int i;
		for(i = 0; i < arr->index; i++)
		{
			free(arr->arr[i]);
		}
		free(arr->arr);
		free(arr);
	}
	return arr;
}
