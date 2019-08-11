#include "dynamicarray.h"

int main()
{
	dArray arr;
	int val = 0;
	int capacity;
	printf("Enter an initial array size: ");
	scanf("%d", &capacity);
	arr = create(capacity);
	while(val >= 0)
	{
		printf("Enter a non negative value (or a negative value to terminate): ");
		scanf("%d", &val);
		if(val >= 0)
		{
			arr = insert(arr, val);
		}
	}
	arrprint(arr);
	destroy(arr);
	return 0;
}
