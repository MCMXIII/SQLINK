#include <stdio.h> 
#include <string.h> 
/*#include <stdlib.h>*/
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <signal.h>

int main()
{
	
	pid_t pid = -1;
	int wtstatus = 0;
	char str[100] = "defalut";
	/*char file[100] = "";*/
	char* const argv[100];
	int i = 0;
	/*char* argument;
	int arg = 0;
	char* nextArgument;*/
	printf("> Welcome to SHELL, type exit to exit\n");
	while(strcmp(str, "exit") != 0)
	{
		if(pid != 0)
		{
			printf("> ");
			scanf("%s", str);
			/*i = -1;
			while(str[i++] != '\n')
			{
				scanf("%c", &str[i]);
			}
			str[i-1] = '\0';*/
			/*argument = strchr(str, ' ');
			if(argument != NULL)
			{
				argument++;
				*(argument - 1) = '\0';
				strcpy(file, str);
				*(argument - 1) = '\n';
				printf("%s\n", argument);
				printf("%s\n", str);
			}
			while(strchr(str, ' ') != NULL)
			{
				nextArgument = strchr(argument, ' ');
				printf("next %s\n", nextArgument);
				if(nextArgument == NULL)
				{
					strcpy(argv[arg], argument);
				}
				else
				{
					*(nextArgument) = '\0';
					strcpy(argv[arg], argument);
					*(nextArgument) = '\n';
					nextArgument++;
				}
				argument = nextArgument;
				printf("%s\n", argument);
				printf("str: %s\n", str);
				arg++;
				printf("...%s\n", strchr(str, ' '));
			}
			for(i = 0; i < arg; i++)
			{
				printf("%s", argv[i]);
			}*/
			pid = fork();
		}
		if(pid == 0)
		{
			if(execvp(str, argv) == -1 && strcmp(str, "exit") != 0)
			{
				printf("Cannot execute program!\n");
				strcpy(str, "exit");
			}
			else
			{
				strcpy(str, "exit");
			}
		}
		else
		{
			waitpid(pid, &wtstatus, 0);
		}
	}
	return 0;
}