#include <stdio.h>
#include <stdlib.h>
#include "bitwise.h"

union Letter
{
  unsigned int m_aToB : 1;
  unsigned int m_cToD : 2;
  unsigned int m_eToH : 3;
  unsigned int m_iToP : 4;
};
struct LetterStruct
{
  int m_bitsNum : 3;
  int m_bitsNum2 : 3;
  union Letter m_l;
  union Letter m_l2;
};
int invert(unsigned char x, unsigned char y)
{
	char output[(8*sizeof(char)) + 1];
	unsigned char out = x;
	int i;
	output[(8*sizeof(char))] = '\0';
	i = (8*sizeof(char)) - 1;
	while(out > 0 || i >= 0)
	{
		output[i] = '0'+(out&1);
		out>>=1;
		i--;
	}
	printf("x = %s\n", output);
	y = ~x;
	out = y;
	output[(8*sizeof(char))] = '\0';
	i = (8*sizeof(char)) - 1;
	while(out > 0 || i >= 0)
	{
		output[i] = '0'+(out&1);
		out>>=1;
		i--;
	}
	printf("x inverted = %s\n", output);
	return y;
}
int rotate(unsigned char x, int rotations)
{
	char output[(8*sizeof(char)) + 1];
	unsigned char out;
	int i, r = rotations;
	int shifts = 0;
	unsigned char rotatedBit = 1;
	out = x;
	output[(8*sizeof(char))] = '\0';
	i = (8*sizeof(char)) - 1;
	while(out > 0 || i >= 0)
	{
		output[i] = '0'+(out&1);
		out>>=1;
		i--;
	}
	printf("x = %s\n", output);
	rotations%=(8*sizeof(char));
	while(rotatedBit > 0)
	{
		rotatedBit<<=1;
		shifts++;
	}
	shifts--;
	while(rotations > 0)
	{
		x = (x>>1) + ((x&1)<<shifts);
		rotations--;
	}
	out = x;
	output[(8*sizeof(char))] = '\0';
	i = (8*sizeof(char)) - 1;
	while(out > 0 || i >= 0)
	{
		output[i] = '0'+(out&1);
		out>>=1;
		i--;
	}
	printf("x rotated by %d = %s\n", r, output);
	return x;
}
int setbits(unsigned char x, int p, int n, unsigned char y)
{
	int rotations = (8*sizeof(char));
	char output[(8*sizeof(char)) + 1];
	unsigned char out;
	int i, index = 0;
	int shifts = 0;
	unsigned char rotatedBit = 1;
	out = x;
	output[(8*sizeof(char))] = '\0';
	i = (8*sizeof(char)) - 1;
	while(out > 0 || i >= 0)
	{
		output[i] = '0'+(out&1);
		out>>=1;
		i--;
	}
	printf("x = %s\n", output);
	out = y;
	output[(8*sizeof(char))] = '\0';
	i = (8*sizeof(char)) - 1;
	while(out > 0 || i >= 0)
	{
		output[i] = '0'+(out&1);
		out>>=1;
		i--;
	}
	printf("y = %s\n", output);
	while(rotatedBit > 0)
	{
		rotatedBit<<=1;
		shifts++;
	}
	shifts--;
	while(rotations > 0)
	{
		if(index < p && index >= p - n)
		{
			x = (x>>1) + ((y&1)<<shifts);
			y>>=1;
		}
		else
		{
			x = (x>>1) + ((x&1)<<shifts);
		}
		index++;
		rotations--;
	}
	out = x;
	output[(8*sizeof(char))] = '\0';
	i = (8*sizeof(char)) - 1;
	while(out > 0 || i >= 0)
	{
		output[i] = '0'+(out&1);
		out>>=1;
		i--;
	}
	printf("setbits n = %d, p = %d gives x = %s\n", n, p, output);
	return x;
}
int setbits2(unsigned int w, int i, int j, int value)
{
	int rotations = (8*sizeof(int));
	char output[(8*sizeof(int)) + 1];
	unsigned int out;
	int k, index = 0;
	int shifts = 0;
	unsigned int rotatedBit = 1;
	if(j < i || j > 31 || i < 0 || value != value % 2)
	{
		printf("Illegal indices or value!");
		return -1;
	}
	out = w;
	output[(8*sizeof(int))] = '\0';
	k = (8*sizeof(int)) - 1;
	while(out > 0 || k >= 0)
	{
		output[k] = '0'+(out&1);
		out>>=1;
		k--;
	}
	printf("w = %s\n", output);
	while(rotatedBit > 0)
	{
		rotatedBit<<=1;
		shifts++;
	}
	shifts--;
	while(rotations > 0)
	{
		if(index <= j && index >= i)
		{
			w = (w<<1) + value;
		}
		else
		{
			w = (w<<1) + ((w&(~0))>>shifts);
		}
		index++;
		rotations--;
	}
	out = w;
	output[(8*sizeof(int))] = '\0';
	k = (8*sizeof(int)) - 1;
	while(out > 0 || k >= 0)
	{
		output[k] = '0'+(out&1);
		out>>=1;
		k--;
	}
	printf("setbits2 i = %d, j = %d, value = %d gives w = %s\n", i, j, value, output);
	return w;
}
char* compress(char* s)
{
	char newChar = 0;
	int i = 0, j = 0;
	printf("Original string: %s\n", s);
	while (s[i] != '\0')
	{
		if(s[i] < 'a' || s[i] > 'p')
		{
			printf("Illegal string!\n");
			return s;
		}
		newChar = (s[i] - 'a')<<4;
		if(s[i+1] == '\0')
		{
			j++;
			break;
		}
		else if(s[i + 1] < 'a' || s[i + 1] > 'p')
		{
			printf("Illegal string!\n");
			return s;
		}
		newChar+=s[i+1] - 'a';
		s[j] = newChar;
		i+=2;
		j++;
	}
	s[j] = '\0';
	printf("Compressed string: ");
	for(i = 0; s[i] != '\0'; i++)
	{
		putchar(((s[i]&240)>>4) + 'a');
		putchar((s[i]&15) + 'a');
	}
	putchar('\n');
	return s;
}
char* compress2(char* s)
{
	int i = 0, j = 0;
	struct LetterStruct * compressedString;
	printf("Original string: %s\n", s);
	while (s[i] != '\0')
	{
		if(s[i] < 'a' || s[i] > 'p')
		{
			printf("Illegal string!\n");
			return s;
		}
		i++;
	}
	compressedString = (struct LetterStruct *)malloc((i/2 + i%2)*sizeof(struct LetterStruct));
	if(compressedString == NULL)
	{
		printf("Cannot compress string!\n");
		return s;
	}
	i = 0;
	while (s[i] != '\0')
	{
		if(s[i] <= 'b')
		{
			compressedString[j].m_bitsNum = 0;
			compressedString[j].m_l.m_aToB = s[i] - 'a';
		}
		else if (s[i] <= 'd')
		{
			compressedString[j].m_bitsNum = 1;
			compressedString[j].m_l.m_cToD = s[i] - 'a';
		}
		else if (s[i] <= 'h')
		{
			compressedString[j].m_bitsNum = 2;
			compressedString[j].m_l.m_eToH = s[i] - 'a';
		}
		else if (s[i] <= 'p')
		{
			compressedString[j].m_bitsNum = 3;
			compressedString[j].m_l.m_iToP = s[i] - 'a';
		}
		if(s[i+1] == '\0')
		{
			i++;
			j++;
			break;
		}
		if(s[i+1] <= 'b')
		{
			compressedString[j].m_bitsNum2 = 0;
			compressedString[j].m_l2.m_aToB = s[i+1] - 'a';
		}
		else if (s[i+1] <= 'd')
		{
			compressedString[j].m_bitsNum2 = 1;
			compressedString[j].m_l2.m_cToD = s[i+1] - 'a';
		}
		else if (s[i+1] <= 'h')
		{
			compressedString[j].m_bitsNum2 = 2;
			compressedString[j].m_l2.m_eToH = s[i+1] - 'a';
		}
		else if (s[i+1] <= 'p')
		{
			compressedString[j].m_bitsNum2 = 3;
			compressedString[j].m_l2.m_iToP = s[i+1] - 'a';
		}
		i+=2;
		j++;
	}
	i = j;
	j = 0;
	while (j < i)
	{
		switch(compressedString[j].m_bitsNum)
		{
			case 0:
			{
				s[j] = compressedString[j].m_l.m_aToB<<4;
				break;
			}
			case 1:
			{
				s[j] = compressedString[j].m_l.m_cToD<<4;
				break;
			}
			case 2:
			{
				s[j] = compressedString[j].m_l.m_eToH<<4;
				break;
			}
			case 3:
			{
				s[j] = compressedString[j].m_l.m_iToP<<4;
				break;
			}
		}
		switch(compressedString[j].m_bitsNum2)
		{
			case 0:
			{
				s[j] += compressedString[j].m_l2.m_aToB;
				break;
			}
			case 1:
			{
				s[j] += compressedString[j].m_l2.m_cToD;
				break;
			}
			case 2:
			{
				s[j] += compressedString[j].m_l2.m_eToH;
				break;
			}
			case 3:
			{
				s[j] += compressedString[j].m_l2.m_iToP;
				break;
			}
		}
		j++;
	}
	s[j] = '\0';
	free(compressedString);
	printf("Compressed string: ");
	for(i = 0; s[i] != '\0'; i++)
	{
		putchar(((s[i]&240)>>4) + 'a');
		putchar((s[i]&15) + 'a');
	}
	putchar('\n');
	return s;
}

