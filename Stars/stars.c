#include <stdio.h>

int func1(int n)
{
	int i;
	for(i = 1; i <= n; i++)
	{
		int j;
		for(j = 0; j < i; j++)
		{
			putchar('*');
		}
		putchar('\n');
	}
	return 0;
}

int func2(int n)
{
	int i;
	for(i = 1; i <= n; i++)
	{
		int j;
		for(j = 0; j < i; j++)
		{
			putchar('*');
		}
		putchar('\n');
	}
	for(i = n-1; i >= 1; i--)
	{
		int j;
		for(j = 0; j < i; j++)
		{
			putchar('*');
		}
		putchar('\n');
	}
	return 0;
}

int func3(int n)
{
	int i;
	int j;
	for(i = 1, j = n - 1; i <= 2*n - 1; i+=2, j--)
	{
		int k;
		for(k = 0; k < j; k++)
		{
			putchar(' ');
		}
		for(k = 0; k < i; k++)
		{
			putchar('*');
		}
		for(k = 0; k < j; k++)
		{
			putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}

int main()
{
	int n = 0;
	printf("Choose a number:");
	scanf("%d", &n);
	func1(n);
	printf("Choose a number:");
	scanf("%d", &n);
	func2(n);
	printf("Choose a number:");
	scanf("%d", &n);
	func3(n);
	return 0;
}
