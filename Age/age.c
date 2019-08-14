#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int i;
	if(argc == 3)
	{
		if((argv[1][1] >= 'A' && argv[1][1] <= 'Z') || (argv[1][1] >= 'a' && argv[1][1] <= 'z'))
		{
			for(i = 0; i < strlen(argv[1]); i++)
			{
				if(!((argv[1][i] >= 'A' && argv[1][i] <= 'Z') || (argv[1][i] >= 'a' && argv[1][i] <= 'z')))
				{
					printf("Invalid input arguments!\n");
					return -1;
				}
			}
			for(i = 0; i < strlen(argv[2]); i++)
			{
				if(!(argv[2][i] >= '0' && argv[2][i] <= '9'))
				{
					printf("Invalid input arguments!\n");
					return -1;
				}
			}
			printf("%s is %d years old.\n", argv[1], atoi(argv[2]));
			return 0;
		}
		else if(argv[1][1] >= '0' && argv[1][1] <= '9')
		{
			for(i = 0; i < strlen(argv[1]); i++)
			{
				if(!(argv[1][i] >= '0' && argv[1][i] <= '9'))
				{
					printf("Invalid input arguments!\n");
					return -1;
				}
			}
			for(i = 0; i < strlen(argv[2]); i++)
			{
				if(!((argv[2][i] >= 'A' && argv[2][i] <= 'Z') || (argv[2][i] >= 'a' && argv[2][i] <= 'z')))
				{
					printf("Invalid input arguments!\n");
					return -1;
				}
			}
			printf("%s is %d years old.\n", argv[2], atoi(argv[1]));
			return 0;
		}
		printf("Invalid input arguments!\n");
		return -1;
	}
	printf("Invalid amount of input arguments!\n");
	return -1;
}
