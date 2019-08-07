#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
	return 0;
}
int main()
{
	int numbers[49];
	int i;
	int j;
	int length = 49;
	int winners[6];
	int rnd = 0;
	char matrix[10][5];
	srand(time(0));
	for(i = 0; i < 49; i++)
	{
		numbers[i] = i+1;
	}
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 5; j++)
		{
			matrix[i][j] = '-';
		}
	}
	matrix[9][4] = ' ';
	for(i = 0; i < 6; i++)
	{
		rnd = rand()%length;
		winners[i] = numbers[rnd];
		numbers[rnd] = 0;
		swap(numbers+(length-1), numbers+rnd);
		length--;
		printf("%d ", winners[i]);
		matrix[(winners[i]-1)%10][winners[i]/10] = '+';
	}
	putchar('\n');
	printf("  1 2 3 4 5 6 7 8 9 10\n");
	for(i = 0; i < 5; i++)
	{
		printf("%d ", i);
		for(j = 0; j < 10; j++)
		{
			putchar(matrix[j][i]);
			putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}
