#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

Bitmap* createBitmap(int numOfFeatures)
{
	int i = 0;
	Bitmap* b = (Bitmap*)malloc(sizeof(Bitmap));
	if(b == NULL)
	{
		return NULL;
	}
	b->m_numOfFeatures = numOfFeatures;
	b->m_featuresArray = (int*)malloc(sizeof(int)*((numOfFeatures/sizeof(int))+1));
	if(b->m_featuresArray == NULL)
	{
		free(b);
		return NULL;
	}
	for(i = 0; i < (numOfFeatures/sizeof(int))+1; i++)
	{
		b->m_featuresArray[i] = 0;
	}
	return b;
}
Bitmap* destroyBitmap(Bitmap* b)
{
	if(b != NULL)
	{
		if(b->m_featuresArray != NULL)
		{
			free(b->m_featuresArray);
		}
		free(b);
	}
	return b;
}
int turnOn(Bitmap * b, int bit)
{
	int i = 0;
	int bitToChange = 1;
	if(b == NULL || b->m_featuresArray == NULL || bit < 0 || bit >= b->m_numOfFeatures)
	{
		return 0;
	}
	while(bit >= 8*sizeof(int))
	{
		i++;
		bit-=8*sizeof(int);
	}
	b->m_featuresArray[i]=b->m_featuresArray[i]|(bitToChange<<bit);
	return 1;
}
int turnOff(Bitmap * b, int bit)
{
	int i = 0;
	int bitToChange = 1;
	if(b == NULL || b->m_featuresArray == NULL || bit < 0 || bit >= b->m_numOfFeatures)
	{
		return 0;
	}
	while(bit >= 8*sizeof(int))
	{
		i++;
		bit-=8*sizeof(int);
	}
	b->m_featuresArray[i]=b->m_featuresArray[i]&(~(bitToChange<<bit));
	return 1;
}
int bitStatus(Bitmap * b, int bit)
{
	int i = 0;
	int bitToChange = 1;
	if(b == NULL || b->m_featuresArray == NULL || bit < 0 || bit >= b->m_numOfFeatures)
	{
		return -1;
	}
	while(bit >= 8*sizeof(int))
	{
		i++;
		bit-=8*sizeof(int);
	}
	return (b->m_featuresArray[i]&(bitToChange<<bit))>0?1:0;
}
int changeBit(Bitmap * b, int bit)
{
	if(bitStatus(b, bit) == 1)
	{
		turnOff(b, bit);
		return 0;
	}
	if(bitStatus(b, bit) == 0)
	{
		turnOn(b, bit);
		return 1;
	}
	return -1;
}
int printBitmap(Bitmap * b)
{
	int i;
	int noOnes = 1;
	unsigned int binary;
	unsigned int max = ~0;
	unsigned int reversed = 0;
	if(b == NULL || b->m_featuresArray == NULL)
	{
		return -1;
	}
	for(i = (b->m_numOfFeatures/(8*sizeof(int))); i >= 0; i--)
	{
		binary = b->m_featuresArray[i];
		max = ~0;
		if(i < (b->m_numOfFeatures/(8*sizeof(int))) && !noOnes)
		{

			while(max >= (binary << 1) && ((binary << 1) >= binary)  && max > 0)
			{
				printf("0");
				max>>=1;
			}
		}
		while(binary)
		{
			reversed<<=1;
			if(binary & 1)
			{
				reversed+=1;
			}
			binary>>=1;
		}
		while(reversed)
		{
			if(reversed & 1)
			{
				printf("1");
			}
			else
			{
				printf("0");
			}
			reversed>>=1;
		}
		binary = b->m_featuresArray[i];
		while(!(binary&1) && binary > 0)
		{
			printf("0");
			binary>>=1;
		}
		if(b->m_featuresArray[i] > 0 && noOnes == 1)
		{
			noOnes = 0;
		}
	}
	printf("\n");
	return 0;
}
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
int printBitmap2(Bitmap * b)/*Uses int2Bin*/
{
	int i;
	int noOnes = 1;
	unsigned int binary;
	unsigned int max = ~0;
	char* output;
	if(b == NULL || b->m_featuresArray == NULL)
	{
		return -1;
	}
	for(i = (b->m_numOfFeatures/(8*sizeof(int))); i >= 0; i--)
	{
		binary = b->m_featuresArray[i];
		max = ~0;
		if(i < (b->m_numOfFeatures/(8*sizeof(int))) && !noOnes)
		{

			while(max >= (binary << 1) && ((binary << 1) >= binary)  && max > 0)
			{
				printf("0");
				max>>=1;
			}
		}
		output = (char*)malloc(32*sizeof(char));
		if(output == NULL)
		{
			return -1;
		}
		printf("%s", int2Bin(binary, output));
		free(output);
		if(b->m_featuresArray[i] > 0 && noOnes == 1)
		{
			noOnes = 0;
		}
	}
	printf("\n");
	return 0;
}
