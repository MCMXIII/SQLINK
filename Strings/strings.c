#include <stdio.h>
#include <string.h>

char* int2Bin(unsigned int x, char* output)
{
	int bitsNum = 0;
	int i;
	if(output == NULL)
	{
		printf("Invalid output string!\n");
		return "";
	}
	for(i = 1; i <= x; i*=2)
	{
		bitsNum++;
	}
	output[bitsNum] = '\0';
	i = bitsNum - 1;
	while(x > 0)
	{
		output[i] = '0'+x%2;
		x/=2;
		i--;
	}
	return output;
}
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
char* squeeze(char* s1, char* s2, char* output)
{
	int i;
	int j;
	int removed = 0;
	if(s1 == NULL)
	{
		printf("Invalid input string!\n");
		return "";
	}
	if(s2 == NULL)
	{
		printf("Invalid filter string!\n");
		return s1;
	}
	if(output == NULL)
	{
		printf("Invalid output string!\n");
		return s1;
	}
	for(i = 0; i < strlen(s2); i++)
	{
		j = 0;
		removed = 0;
		while(s1[j] != '\0')
		{
			if(s1[j] == s2[i])
			{
				removed++;
			}
			else
			{
				output[j - removed] = s1[j];
			}
			j++;
		}
		output[j - removed] = s1[j];
		s1 = output;
	}
	return s1;
}
int location(char* s1, char* s2)
{
	int i;
	int j;
	int k;
	if(s1 == NULL)
	{
		printf("Invalid string!\n");
		return -1;
	}
	if(s2 == NULL)
	{
		printf("Invalid substring!\n");
		return -1;
	}
	for(i = 0; i < strlen(s1); i++)
	{
		if(s1[i] == s2[0])
		{
			k = i+1;
			j = 1;
			while(s1[k] == s2[j])
			{
				k++;
				j++;
			}
			if(s2[j] == '\0')
			{
				return i;
			}
		}
	}
	return -1;
}
int main()
{
	char output[100];
	int	intInput = 0;
	char stringInput[100];
	char stringInput2[100];
	char inputBase = 'x';
	while (intInput >= 0 && stringInput[0] != '-')
	{
		while(inputBase != 'b' && inputBase != 'd')
		{
			if(inputBase != '\n')
			{
				printf("Press b for a binary input and d for a decimal input: ");
			}
			scanf("%c", &inputBase);
		}
		printf("Please enter a non negative number: ");
		switch(inputBase)
		{
			case 'b':
			{
				scanf("%s", stringInput);
				if(stringInput[0] == '-')
				{
					break;
				}
				if (bin2Int(stringInput) >= 0)
				{
					printf("The decimal representation of %s is %d.\n", stringInput, bin2Int(stringInput));
				}
				break;
			}
			case 'd':
			{
				scanf("%d", &intInput);
				if(intInput < 0)
				{
					break;
				}
				printf("The decimal representation of %d is %s.\n", intInput, int2Bin(intInput, output));
				break;
			}
			default:
			{
				break;
			}
		}
		inputBase = 'x';
		printf("\n");
	}
	/*printf("%s\n", int2Bin(31, output));*/
	/*printf("%s\n", int2Bin(31, output2));*/
	/*printf("%d\n", bin2Int("10101"));*/
	/*printf("%d\n", bin2Int(output2));*/
	/*printf("%d\n", bin2Int("93ak1"));*/
	printf("Enter a string: ");
	scanf("%s", stringInput);
	printf("Enter chars filter: ");
	scanf("%s", stringInput2);
	printf("Your squeezed string is %s.\n", squeeze(stringInput, stringInput2, output));
	printf("Enter a string: ");
	scanf("%s", stringInput);
	printf("Enter a substring to find: ");
	scanf("%s", stringInput2);
	printf("The location of %s in %s is %d.\n", stringInput2, stringInput, location(stringInput, stringInput2));
	return 0;
}
