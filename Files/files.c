#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"

struct wordcounter {
	char* word;
	int amount;
};
int printLastN(int n, char* dir)
{
	FILE * f = fopen(dir, "r");
	int i = 0, j;
	char** rows;
	if(f == NULL || n <= 0)
	{
		return -1;
	}
	rows = (char**)malloc(n*(sizeof(char*)));
	for(j = 0; j < n; j++)
	{
		rows[j] = (char*)malloc(512*(sizeof(char)));
		if(rows[j] == NULL)
		{
			for(--j; j > 0; j--)
			{
				free(rows[j]);
			}
			free(rows);
			return -1;
		}
	}
	while(fgets(rows[i], 512, f) != NULL)
	{
		i++;
		if(i == n)
		{
			i = 0;
		}
	}
	j = i;
	while(j < n)
	{
		if(rows[j][0] != '\0')
		{
			printf("%s",rows[j]);
		}
		j++;
	}
	j = 0;
	while(j < i)
	{
		printf("%s", rows[j]);
		j++;
	}
	printf("\n");
	for(j = 0; j < n; j++)
	{
		free(rows[j]);
	}
	free(rows);
	fclose(f);
	return 0;
}
int charcount(char* dir)
{
	FILE * f = fopen(dir, "r");
	int i;
	char current;
	int* counter;
	if(f == NULL)
	{
		return -1;
	}
	counter = (int*)malloc(256*sizeof(int));
	if(counter == NULL)
	{
		return -1;
	}
	for(i = 0; i < 256; i++)
	{
		counter[i] = 0;
	}
	while((current = fgetc(f)) != EOF)
	{
		counter[((int)current + 128)]++;
	}
	for(i = -128; i+128 < 256; i++)
	{
		current = (char)i;
		if(counter[((int)current + 128)] > 0)
		{
			printf("%c: %d\n", current, counter[((int)current + 128)]);
		}
	}
	free(counter);
	fclose(f);
	return 0;
}
int wordcount(char* dir)
{
	FILE * f = fopen(dir, "r");
	int i, spacecounter = 0;
	char* current;
	char c;
	wordcounter counter;
	if(f == NULL)
	{
		return -1;
	}
	while((c = fgetc(f)) != EOF)
	{
		if(c == ' ' || c == '\n' || c == '\t')
		{
			spacecounter++;
		}
	}
	fclose(f);
	counter = (wordcounter)malloc((spacecounter+1)*sizeof(struct wordcounter));
	if(counter == NULL)
	{
		return -1;
	}
	for(i = 0; i < spacecounter + 1; i++)
	{
		counter[i].amount = 0;
		counter[i].word = (char*)malloc(512*(sizeof(char)));
	}
	f = fopen(dir, "r");
	if(f == NULL)
	{
		return -1;
	}
	current = (char*)malloc(512*(sizeof(char)));
	if(current == NULL)
	{
		return -1;
	}
	while(fscanf(f, "%s", current) != EOF)
	{
		for(i = 0; counter[i].amount > 0; i++)
		{
			if(strcmp(current, counter[i].word) == 0)
			{
				counter[i].amount++;
				break;
			}
		}
		if(counter[i].amount == 0)
		{
			strcpy(counter[i].word, current);
			counter[i].amount++;
		}
	}
	for(i = 0; counter[i].amount > 0 && i <= spacecounter; i++)
	{
		if(counter[i].amount > 0)
		{
			printf("%s: %d\n", counter[i].word, counter[i].amount);
		}
	}
	for(i = 0; i < spacecounter + 1; i++)
	{

		free(counter[i].word);
	}
	free(counter);
	free(current);
	fclose(f);
	return 0;
}
