#include "memPool_t.h"
#include "memPage_t.h"
#include <string.h>
#include <iostream>

char* memPool_t::read(void* output, unsigned int bytes)
{
	unsigned int index = 0;	
	unsigned int returnLength = bytes;
	if(output != 0)
	{
		if(position + bytes > size)
		{
			returnLength = size - position;
		}
		index+=capacity - (position%capacity);
		(*(pbuffer[position/capacity])).read(output, position%capacity, returnLength);
		position += returnLength < index?returnLength:index;
		returnLength = returnLength > index?returnLength-index:0;
		while(returnLength >= capacity)
		{		
			(*(pbuffer[position/capacity])).read((void*)(&((unsigned char*)output)[index]), 0, capacity);
			index+=capacity;
			returnLength-=capacity;
			position+=capacity;
		}
		if(returnLength > 0)
		{
			(*(pbuffer[position/capacity])).read((void*)(&((unsigned char*)output)[index]), 0, returnLength);
			position+=returnLength;
		}		
	}
	else
	{
		cout << "Undefined output buffer!\n";	
	}
	return (char*)output;
}
char* memPool_t::read(void* output, const unsigned int pos, unsigned int bytes)
{
	if(pos <= size)
	{
		position = pos;
		read(output, bytes);
	}
	else
	{
		cout << "Invalid position!\n";
	}
	return (char*)output;
}
unsigned int memPool_t::write(const void* bytes, unsigned int amountToWrite)
{
	if(bytes == 0)
	{
		cout << "Undefined input, no write was done!\n";
		return 0;
	}
	unsigned int index = 0;
	unsigned int written;
	unsigned int ret = amountToWrite;
	unsigned int oldSize = size;
	if(size < position + amountToWrite)
	{
		size = position + amountToWrite;
	}
	while(amountToWrite > 0)
	{
		written = (*(pbuffer[position/capacity])).write(position%capacity, (void*)(&((unsigned char*)bytes)[index]), amountToWrite);
		amountToWrite-=written;
		index+=written;
		position+=written;
		if(position >= oldSize && position%capacity == 0)
		{
			pbuffer.insert(pbuffer.end(), new memPage_t(capacity));
		}
	}
	return ret;
}
unsigned int memPool_t::write(const unsigned int pos, const void* bytes, unsigned int amountToWrite)
{
	if(pos > size)
	{
		cout << "Invalid position!\n";
		return 0;
	}
	position = pos;
	return write(bytes, amountToWrite);
}
void memPool_t::setCapacity(unsigned int newCap)
{
	if(newCap == 0)
	{
		cout << "Cannot set a zero capacity!\n";
		return;
	}
	unsigned int originalSize = size;
	char* tempBuffer = new char[size];
	read((void*)tempBuffer, 0, size);
	pbuffer.clear();
	size = 0;
	position = 0;
	capacity = newCap;
	pbuffer.insert(pbuffer.end(), new memPage_t(capacity));
	write((void*)tempBuffer, originalSize);
}