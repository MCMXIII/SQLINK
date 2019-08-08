#include <stdio.h>

int strcmp2(char* x, char* y)
{
	int i = 0;
	while(x[i] == y[i] && x[i] != '\0')
	{
		i++;
	}
	return x[i] - y[i];
}


int strcpy2(char* x, char* y)
{
	int i = 0;
	while (y[i-1] != '\0')
	{
		x[i] = y[i];
		i++;
	}
	return 0;
}
char* strcat2(char* strDst, char* strSrc)
{
	int i = 0;
	int j = 0;
	while (strDst[i] != '\0')
	{
		i++;
	}
	while (strSrc[j] != '\0')
	{
		strDst[i] = strSrc[j];
		i++;
		j++;
	}
	return strDst;
}

int main()
{
	char s1[9];
	char s2[9] = "Mahrozet";
	char s3[9] = "Mahr";
	printf("%d %d %d\n", strcmp2("Mahrozet", "Mahrozat"), strcmp2("Mahrozet", "Makhrozet"), strcmp2("Mahrozet", "Mahrozet"));
	strcpy2(s1, s2);
	printf("%s\n", s1);
	printf("%s\n", strcat2(s3, "ozet"));
	return 0;
}
