#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include "md5.h"
#include "fileOps.h"

typedef enum {
	DIRECTORY = 4,
	REGFILE = 8
} filetype;
void doNothing(void* element)
{
	return;
}
void zeroString(char* str, int len)
{
	int i;
	for(i = 0; i < len - 1; i++)
	{
		str[i] = 0;
	}
	str[len - 1] = '\0';
}
void findOrAdd(hashTable* t, unsigned char* key, char* path, FILE* output)
{
	char* value;
	unsigned char* tableKey;
	if(path == NULL)
	{
		return;
	}
	if(hashTableFind(t, key) != NULL)
	{
		printf("%s is a duplicate file of %s!\n", path, (char*)hashTableFind(t, key));
		fprintf(output, "%s is a duplicate file of %s!\n", path, (char*)hashTableFind(t, key));
	}
	else
	{
		tableKey = (unsigned char*)malloc((strlen(key)+1)*sizeof(unsigned char));
		if(tableKey == NULL)
		{
			printf("Error in hashing key!\n");
			fprintf(output, "Error in hashing key!\n");
		}
		else
		{
			strcpy(tableKey, key);
			value = (char*)malloc((strlen(path)+1)*sizeof(char));
			if(value == NULL)
			{
				printf("Error in hashing value!\n");
				fprintf(output, "Error in hashing value!\n");
				free(tableKey);
			}
			else
			{
				strcpy(value, path);
				if(hashTableInsert(t, (void*)tableKey, (void*)value, 'n', doNothing) != OK)
				{
					printf("Error in hashing!\n");
					fprintf(output, "Error in hashing!\n");
				}
			}
		}
	}
}
void findDuplicates(const char *name, hashTable* t, FILE* output)
{
	DIR *dir;
	struct dirent *entry;
	char path[1024];
	unsigned char key[17];
	FILE* f;
	if(name[0] == '\0')
	{
		return;
	}
	if (!(dir = opendir(name)))
	{
		return;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		zeroString(path, 1024);
		snprintf(path, sizeof(path), "%s/%s\0", name, entry->d_name);
		if (entry->d_type == DIRECTORY)
		{
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			{
				continue;
			}
			findDuplicates(path, t, output);
		}
		else if(entry->d_type == REGFILE)
		{
			if(strcmp(path, "./duplicates.txt") == 0)
			{
				continue;
			}
			f = fopen(path, "rb");
			if(f == NULL)
			{
				printf("Error in opening file!\n");
				fprintf(output, "Error in opening file!\n");
				continue;
			}
			zeroString(key, 17);
			generateKey(f, key);
			findOrAdd(t, key, path, output);
			fclose(f);
		}
	}
	closedir(dir);
}
