#include "files.h"
#include <stdio.h>

int main()
{
	char input[100];
	int n;
	printf("Enter a positive rows number n:\n");
	scanf("%d", &n);
	printf("Enter a file name to print its last n rows:\n");
	scanf("%s", input);
	printLastN(n, input);
	printf("Enter a file name to count its characters:\n");
	scanf("%s", input);
	charcount(input);
	printf("Enter a file name to count its words:\n");
	scanf("%s", input);
	wordcount(input);
	return 0;
}
