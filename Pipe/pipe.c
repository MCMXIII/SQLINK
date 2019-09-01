#include <stdio.h> 
#include <string.h> 
/*#include <stdlib.h>*/
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <signal.h>

int main()
{
	pid_t process;
	char input[160];
	int parr[2];
	int wtstatus = 0;
	pipe(parr);
	process = fork();
	if(process > 0)
	{
		write(parr[1], "Hello son...\n", 160);
		waitpid(0, &wtstatus, 0);
		while(read(parr[0], input, 160) > 0)
		{
			printf("Son to %d: %s", getpid(), input);
			break;
		}
	}
	else
	{
		waitpid(process, &wtstatus, 0);
		while(read(parr[0], input, 160) > 0)
		{
			printf("Father to %d: %s", getpid(), input);
			break;
		}
		write(parr[1], "Hello Father...\n", 160);
	}
	return 0;
}