#include <stdio.h>
#include <stdlib.h>

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

	typedef struct dArr* dArray;
	dArray create(int capacity);
	dArray insert(dArray arr, int* valp);
	dArray insertInt(dArray arr, int val);
	dArray arrprint(dArray arr);
	dArray destroy(dArray arr);

#endif
