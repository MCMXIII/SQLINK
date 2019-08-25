#include <stdio.h>
#include "bstree.h"
#include <stdlib.h>
#include <time.h>

void printNum(int num)
{
	printf("%d ", num);
}
tree* generateRandomTree()
{
	int additions = 0;
	int searches = 0;
	int removals = 0;
	int value = 0;
	int i = 0;
	tree* t;
	bstCreate(&t);
	srand(time(0));
	additions = (rand()%32)+1;
	for(i = 0; i < additions; i++)
	{
		value = (rand()%100)+1;
		bstInsert(t, value);
		bstWalk(t, In, printNum);
		printf("\n");
	}
	bstWalk(t, In, printNum);
	printf("\n");
	bstWalk(t, Pre, printNum);
	printf("\n");
	bstWalk(t, Post, printNum);
	printf("\n");
	searches = (rand()%20)+1;
	for(i = 0; i < searches; i++)
	{
		value = (rand()%100)+1;
		if(bstSearch(t, value) == OK)
		{
			printf("%d is in ", value);
		}
		else
		{
			printf("%d is not in ", value);
		}
		bstWalk(t, In, printNum);
		printf(".\n");
	}
	if(additions < 2)
	{
		removals = 1;
	}
	else
	{
		removals = (rand()%(additions - 1))+1;
	}
	for(i = 0; i < removals; i++)
	{
		value = (rand()%100)+1;
		if(bstDelete(t, value) == OK)
		{
			printf("%d was deleted successfully from ", value);
		}
		else
		{
			printf("%d was not deleted successfully from ", value);
		}
		bstWalk(t, In, printNum);
		printf(".\n");
	}
	return t;
}
int main()
{
	tree* t;
	bstInsert(t, 7);
	bstWalk(t, In, printNum);
	printf("\n");
	t = generateRandomTree();
	printf("%d\n", bstDestroy(t));
	return 0;
}