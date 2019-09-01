#include <stdio.h>

int a(int x);
int b();
int a(int x)
{
	printf("It's a!\n");
	*(&x - 1) = (int)b;
	return 0;
}

int b()
{
	printf("It's b!\n");
	return 0;
}

int main()
{
	printf("It's main!\n");
	a(0);
	printf("It's main again!\n");	
}

