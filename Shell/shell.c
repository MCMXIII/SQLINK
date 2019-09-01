#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <signal.h>

int main()
{
	
	pid_t pid = -1;
	int wtstatus = 0;
	char str[100] = "defalut";
	char file[100] = "";
	char argv[100][100];
	char* args[100];
	int i = 0;
	int argsExist = 0;
	char* argument;
	int arg = 0;
	char* nextArgument;
	printf("> Welcome to SHELL, type exit to exit\n");
	while(strcmp(str, "exit") != 0)
	{
		if(pid != 0)
		{
			argsExist = 0;
			arg = 0;
			for(i = 0; i < 100; i++)
			{
				args[i] = NULL;
				
			}
			printf("> ");
			/*scanf("%s", str);*/
			i = -1;
			while(str[i++] != '\n')
			{
				scanf("%c", &str[i]);
			}
			str[i-1] = '\0';
			argument = strchr(str, ' ');
			if(argument != NULL)
			{
				argument++;
				*(argument - 1) = '\0';
				strcpy(file, str);
				*(argument - 1) = '\n';
				argsExist = 1;
			}
			else
			{
				strcpy(file, str);
			}
			while(strchr(str, ' ') != NULL)
			{
				nextArgument = strchr(argument, ' ');
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
				arg++;
			}
			if(argsExist)
			{
				strcpy(argv[arg], argument);
				arg++;
			}
			/*args = (char**)malloc(arg*sizeof(char*));*/
			for(i = 0; i < arg; i++)
			{
				args[i] = argv[i];
				
			}
			pid = fork();
		}
		if(pid == 0)
		{
			if(execvp(file, args) == -1 && strcmp(str, "exit") != 0)
			{
				printf("Cannot execute program!\n");
				strcpy(str, "exit");
			}
			else
			{
				strcpy(str, "exit");
			}
			/*free(args);*/
		}
		else
		{
			waitpid(pid, &wtstatus, 0);
		}
	}
	return 0;
}