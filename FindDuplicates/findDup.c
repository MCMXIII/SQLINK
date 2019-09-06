#include "init.h"
#include "fileOps.h"
#include <stdio.h>

int main()
{
	FILE* output = fopen("duplicates.txt", "w");
	hashTable* t = initializeHashTable();
	if(output == NULL)
	{
		printf("Cannot create output file!\n");
		return;
	}
	fprintf(output, "Duplicates:\n");
	if(t == NULL)
	{
		return;
	}
	findDuplicates(".", t, output);
	fclose(output);
	destroyHashTable(t);
}