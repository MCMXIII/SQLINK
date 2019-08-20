#include <stdlib.h>
#include "darray.h"

struct darray
{
	size_t m_initial_capacity;
	size_t m_capacity;
	int m_amount;
	int* m_arr;
};

AdtStatus darrayCreate(darray **dArr, size_t initial_capacity)
{
	*dArr = (darray *)malloc(sizeof(darray));
	if(*dArr == NULL || initial_capacity <= 0)
	{
		return AllocationError;
	}
	(*dArr)->m_amount = 0;
	(*dArr)->m_initial_capacity = initial_capacity;
	(*dArr)->m_capacity = initial_capacity;
	(*dArr)->m_arr = (int *)malloc((*dArr)->m_initial_capacity*sizeof(int));
	if((*dArr)->m_arr == NULL)
	{
		return AllocationError;
	}
	return OK;
}
AdtStatus darrayDestroy(darray *dArr)
{
	if(dArr == NULL || dArr->m_arr == NULL)
	{
		if(dArr != NULL)
		{
			free(dArr);
			return AllocationError;
		}
		return AllocationError;
	}
	free(dArr->m_arr);
	free(dArr);
	return OK;
}
/* Add number to the end. */
AdtStatus   darrayAdd(darray *dArr,  int  _item)
{
	if(dArr == NULL || dArr->m_arr == NULL || dArr->m_capacity <= 0)
	{
		return AllocationError;
	}	
	if(dArr->m_amount == dArr->m_capacity)
	{
		dArr->m_arr = (int*)realloc(dArr->m_arr, 2*dArr->m_capacity*sizeof(int));
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
AdtStatus   darrayDelete(darray *dArr,  int* _item)
{
	if(dArr == NULL || dArr->m_arr == NULL || dArr->m_capacity <= 0)
	{
		return AllocationError;
	}
	if((dArr->m_amount <= ((3*dArr->m_capacity)/8)) && (dArr->m_capacity/2 >= dArr->m_initial_capacity))
	{ 
		dArr->m_arr = (int*)realloc(dArr->m_arr, (dArr->m_capacity*sizeof(int)/2));
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
AdtStatus   darrayGet(darray *dArr, size_t _index, int *_item)
{
	if(dArr == NULL || dArr->m_arr == NULL)
	{
		return AllocationError;
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
AdtStatus   darraySet(darray *dArr, size_t _index, int  _item)
{
	if(dArr == NULL || dArr->m_arr == NULL)
	{
		return AllocationError;
	}
	if(_index >= dArr->m_amount)
	{
		return IndexError;
	}
	dArr->m_arr[_index] = _item;
	return OK;
}
AdtStatus   darrayItemsNum(darray *dArr, int*  _numOfItems)
{
	if(dArr == NULL || dArr->m_arr == NULL)
	{
		return AllocationError;
	}
	if(_numOfItems != NULL)
	{
		*_numOfItems = dArr->m_amount;
	}
	return OK;
}
AdtStatus darraySort(darray *dArr, size_t arraySize)
{
	int sorted = 0;
	int i = 0;
	int temp;
	if(dArr == NULL || dArr->m_arr == NULL)
	{
		return AllocationError;
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
			if(dArr->m_arr[i] > dArr->m_arr[i+1])
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
