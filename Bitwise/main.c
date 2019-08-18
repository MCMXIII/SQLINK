#include <stdio.h>
#include <string.h>
#include "bitwise.h"

int bin2Int(char* x)
{
	int output = 0;
	int i;
	int size = 1;
	if(x == NULL)
	{
		printf("Invalid input string!\n");
		return -1;
	}
	for(i = 0; i < strlen(x); i++)
	{
		if(x[i] > '1' || x[i] < '0')
		{
			printf("Invalid input string!\n");
			return -1;
		}
	}
	for(i = strlen(x) - 1; i >= 0; i--)
	{
		output+=size*(x[i]-'0');
		size*=2;
	}
	return output;
}
int main()
{
	unsigned char y = '0';
	char str[100];
	char input1[8];
	char input2[8];
	char input3[32];
	int intInput1 = 0;
	int intInput2 = 0;
	int intInput3 = 0;
	unsigned char convertedBin1 = 0, convertedBin2 = 0;
	unsigned int convertedBin3 = 0;
	while(convertedBin1 == 0)
	{
		printf("Enter a binary number:\n");
		scanf("%s", input1);
		convertedBin1 = bin2Int(input1);
	}
	y = invert(convertedBin1, y);
	convertedBin1 = 0;
	while(convertedBin1 == 0)
	{
		printf("Enter a binary number:\n");
		scanf("%s", input1);
		convertedBin1 = bin2Int(input1);
	}
	intInput1 = -1;
	while(intInput1 < 0)
	{
		printf("Enter an amount of rotations:\n");
		scanf("%d", &intInput1);
	}
	rotate(convertedBin1, intInput1);
	convertedBin1 = 0;
	while(convertedBin1 == 0)
	{
		printf("Enter a binary number:\n");
		scanf("%s", input1);
		convertedBin1 = bin2Int(input1);
	}
	convertedBin2 = 0;
	while(convertedBin2 == 0)
	{
		printf("Enter another binary number:\n");
		scanf("%s", input2);
		convertedBin2 = bin2Int(input2);
	}
	intInput1 = -1;
	while(intInput1 < 0)
	{
		printf("Enter an index in your first binary number:\n");
		scanf("%d", &intInput1);
	}
	intInput2 = -1;
	while(intInput2 < 0)
	{
		printf("Enter an amount of digits from your second binary number:\n");
		scanf("%d", &intInput2);
	}
	setbits(convertedBin1, intInput1, intInput2, convertedBin2);
	convertedBin3 = 0;
	while(convertedBin3 == 0)
	{
		printf("Enter a binary number:\n");
		scanf("%s", input3);
		convertedBin3 = bin2Int(input3);
	}
	intInput1 = -1;
	while(intInput1 < 0)
	{
		printf("Enter an index in your binary number:\n");
		scanf("%d", &intInput1);
	}
	intInput2 = -1;
	while(intInput2 < 0)
	{
		printf("Enter a bigger index in your binary number:\n");
		scanf("%d", &intInput2);
	}
	intInput3 = -1;
	while(intInput3 < 0 || intInput3 > 1)
	{
		printf("Enter a bit:\n");
		scanf("%d", &intInput3);
	}
	setbits2(convertedBin3, intInput1, intInput2, intInput3);
	printf("Enter a string of chars from a to p:\n");
	scanf("%s", str);
	compress(str);
	printf("Enter a string of chars from a to p:\n");
	scanf("%s", str);
	compress2(str);
	return 0;
}
