#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _POSIX_C_SOURCE 199309L

void declongtoa(long number, char* buffer)
{
	int digits = 0, i;
	long x = number;
	if(x <= 0)
	{
		digits++;
		x*=-1;
	}
	while(x > 0)
	{
		x/=10;
		digits++;
	}
	if(number < 0)
	{
		x = -1;
	}
	else
	{
		x = 0;
	}
	buffer[digits] = '\0';
	for(i = digits - 1; i >= 0; i--)
	{
		buffer[i] = '0' + number%10;
		number/=10;
	}
	if(x == -1)
	{
		buffer[0] = '-';
	}
}

void action(int signum, siginfo_t *siginfo, void *context)
{
	char output[20] = "\nPID: ";
	char id[20];
	declongtoa((long)siginfo->si_pid, id);
	strcat(output, id);
	strcat(output, "\n");
	write(1, output, strlen(output));
	exit(0);
}

int main()
{
	struct sigaction act;
	sigset_t t;
	act.sa_handler = NULL;
	act.sa_mask = t;
	act.sa_restorer = NULL;
	act.sa_sigaction = &action;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT/*TERM*/, &act, NULL);
	printf("Before interrupt!\n");
	/*kill(0, SIGTERM);*/
	while(1){}
	return 0;
}
