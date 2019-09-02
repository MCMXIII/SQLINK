#include "progB.h"
#include <stdio.h>

int progAFunc()
{
	printf("I'm ProgAFunc\n");
	return 0;
}

int main()
{
	progAFunc();
	progBFunc();
	lib1Func();
	lib2Func();
	lib3Func();
	return 0;
}