#include <stdlib.h>
#include "darray.h"

struct darray
{
	size_t m_initial_capacity;
	size_t m_capacity;
	int m_amount;
	void** m_arr;
};

AdtStatus darrayCreate(darray **dArr, size_t initial_capacity)
{
	*dArr = (darray *)malloc(sizeof(darray));
	if(*dArr == NULL || initial_capacity <= 0)
	{
		if(*dArr != NULL)
		{
			free(*dArr);
		}
		return AllocationError;
	}
	(*dArr)->m_amount = 0;
	(*dArr)->m_initial_capacity = initial_capacity;
	(*dArr)->m_capacity = initial_capacity;
	(*dArr)->m_arr = (void**)malloc((*dArr)->m_initial_capacity*sizeof(void*));
	if((*dArr)->m_arr == NULL)
	{
		free(*dArr);
		return AllocationError;
	}
	return OK;
}
AdtStatus darrayDestroy(darray *dArr, elementDestroy destroyFunc, void *context)
{
	int i = 0;
	if(destroyFunc == NULL)
	{
		return UndeclaredError;
	}
	if(dArr == NULL || dArr->m_arr == NULL)
	{
		if(dArr != NULL)
		{
			free(dArr);
		}
		return UndeclaredError;
	}
	for(i = 0; i < dArr->m_amount; i++)
	{
		if(dArr->m_arr[i] != NULL)
		{
			destroyFunc((void*)(dArr->m_arr[i]), context);
		}
	}
	free(dArr->m_arr);
	free(dArr);
	return OK;
}
/* Add number to the end. */
AdtStatus   darrayAdd(darray *dArr,  void  *_item)
{
	if(dArr == NULL || dArr->m_arr == NULL || dArr->m_capacity <= 0 || _item == NULL)
	{
		return UndeclaredError;
	}	
	if(dArr->m_amount == dArr->m_capacity)
	{
		dArr->m_arr = (void**)realloc(dArr->m_arr, 2*dArr->m_capacity*sizeof(void*));
		if(dArr->m_arr == NULL)
		{
			return AllocationError;
		}
		dArr->m_capacity*=2;
	}
	dArr->m_arr[dArr->m_amount++] = _item;
	return OK;
}
/* Delete number from the end. */
AdtStatus   darrayDelete(darray *dArr,  void** _item)
{
	if(dArr == NULL || dArr->m_arr == NULL || dArr->m_capacity <= 0 || _item == NULL)
	{
		return UndeclaredError;
	}
	if((dArr->m_amount <= ((3*dArr->m_capacity)/8)) && (dArr->m_capacity/2 >= dArr->m_initial_capacity))
	{ 
		dArr->m_arr = (void**)realloc(dArr->m_arr, (dArr->m_capacity*sizeof(void*)/2));
		if(dArr->m_arr == NULL)
		{
			return AllocationError;
		}
		dArr->m_capacity/=2;
	}
	if(_item != NULL)
	{
		*_item = dArr->m_arr[dArr->m_amount - 1];
	}
	dArr->m_arr[--dArr->m_amount] = 0;
	return OK;
}
AdtStatus   darrayGet(darray *dArr, size_t _index, void **_item)
{
	if(dArr == NULL || dArr->m_arr == NULL || _item == NULL)
	{
		return UndeclaredError;
	}
	if(_index >= dArr->m_amount)
	{
		return IndexError;
	}
	if(_item != NULL)
	{
		*_item = dArr->m_arr[_index];
	}
	return OK;
}
AdtStatus   darraySet(darray *dArr, size_t _index, void* _item, void** _previous)
{
	if(dArr == NULL || dArr->m_arr == NULL)
	{
		return UndeclaredError;
	}
	if(_index >= dArr->m_amount)
	{
		return IndexError;
	}
	*_previous = dArr->m_arr[_index];
	dArr->m_arr[_index] = _item;
	return OK;
}
AdtStatus   darrayItemsNum(darray *dArr, int*  _numOfItems)
{
	if(dArr == NULL || dArr->m_arr == NULL)
	{
		return UndeclaredError;
	}
	if(_numOfItems != NULL)
	{
		*_numOfItems = dArr->m_amount;
	}
	return OK;
}
AdtStatus darraySort(darray *dArr, elementCompare cmp)
{
	int sorted = 0;
	int i = 0;
	void* temp;
	if(dArr == NULL || dArr->m_arr == NULL)
	{
		return UndeclaredError;
	}
	if(dArr->m_capacity <= 0)
	{
		return IndexError;
	}
	if(dArr->m_amount <= 1)
	{
		return AmountError;
	}
	while(!sorted)
	{
		sorted = 1;
		for(i = 0; i < dArr->m_amount - 1; i++)
		{
			if(cmp(dArr->m_arr[i], dArr->m_arr[i+1]) > 0)
			{
				sorted = 0;
				temp = dArr->m_arr[i];
				dArr->m_arr[i] = dArr->m_arr[i+1];
				dArr->m_arr[i+1] = temp;
			}
		}
	}
	return OK;
}
AdtStatus darrayQuickSort(darray *dArr, elementCompare cmp, int first, int last)
{
	int counter = 0;
	int i = first + 1, j = last;
	void* temp;
	if(dArr == NULL || dArr->m_arr == NULL)
	{
		return UndeclaredError;
	}
	if(dArr->m_capacity <= 0)
	{
		return IndexError;
	}
	if(dArr->m_amount <= 1)
	{
		return AmountError;
	}
	if(first >= last)
	{
		return OK;
	}
	if(i == j)
	{
		if(cmp(dArr->m_arr[i], dArr->m_arr[first]) < 0)
		{
			temp = dArr->m_arr[i];
			dArr->m_arr[i] = dArr->m_arr[first];
			dArr->m_arr[first] = temp;
		}
	}
	else
	{
		counter = first;
		while(i < j)
		{
			while(cmp(dArr->m_arr[i], dArr->m_arr[first]) <= 0 && i <= last)
			{
				counter++;
				i++;
			}
			while(cmp(dArr->m_arr[j], dArr->m_arr[first]) > 0 && j > first)
			{
				j--;
			}
			if(i < j)
			{
				temp = dArr->m_arr[i];
				dArr->m_arr[i] = dArr->m_arr[j];
				dArr->m_arr[j] = temp;
			}
		}
		temp = dArr->m_arr[first];
		dArr->m_arr[first] = dArr->m_arr[counter];
		dArr->m_arr[counter] = temp;
		darrayQuickSort(dArr, cmp, first, counter - 1);
		darrayQuickSort(dArr, cmp, counter + 1, last);
	}
	return OK;
}
