#include "dynamicparray.h"

int main()
{
	int i = 0;
	dArray arr;
	int val = 0;
	int* valp;
	int capacity;
	printf("Enter an initial array size: ");
	scanf("%d", &capacity);
	arr = create(capacity);
	if(arr == NULL)
	{
		printf("Error! cannot create array!");
		return 0;
	}
	while(val >= 0)
	{
		printf("Enter a non negative value (or a negative value to terminate): ");
		scanf("%d", &val);
		valp = (int*)malloc(sizeof(int));
		*valp = val;
		if(val >= 0)
		{
			/*if(i % 2 == 0)
			{*/
				arr = insert(arr, valp);
			/*}
			else
			{
				arr = insertInt(arr, val);
			}
			i++;*/
		}
	}
	arrprint(arr);
	destroy(arr);
	return 0;
}
