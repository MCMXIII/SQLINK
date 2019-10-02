#include "memPage_t.h"
#include <string.h>
#include <iostream>

/*void memPage_t::setCapacity(unsigned int newCap)
{
	char* tempBuffer = new char[capacity];
	if(newCap > capacity)
	{
		memcpy((void*)tempBuffer, (void*)buffer, capacity);
		delete [] buffer;
		buffer = new char[newCap];
		memcpy((void*)buffer, (void*)tempBuffer, capacity);
		capacity = newCap;
	}
	else if(capacity > newCap)
	{
		if(position > newCap)
		{
			position = newCap;
		}
		memcpy((void*)tempBuffer, (void*)buffer, newCap);
		delete [] buffer;
		buffer = new char[newCap];
		memcpy((void*)buffer, (void*)tempBuffer, newCap);
		capacity = newCap;
	}
}*/
char* memPage_t::read(void* output, unsigned int bytes)
{
	if(output != 0)
	{
		if(position + bytes > size)
		{
			memcpy(output, (void *)(&(buffer[position])), size - position);
			position = size;
		}
		else
		{
			memcpy(output, (void *)(&(buffer[position])), bytes);
			position += bytes;
		}
	}
	else
	{
		cout << "Undefined output buffer!\n";	
	}
	return (char*)output;
}
char* memPage_t::read(void* output, const unsigned int pos, unsigned int bytes)
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
unsigned int memPage_t::write(const void* bytes, unsigned int amountToWrite)
{
	if(bytes == 0)
	{
		cout << "Undefined input, no write was done!\n";
		return 0;
	}
	unsigned int ret;
	if(position + amountToWrite > capacity)
	{
		memcpy((void *)(&(buffer[position])), bytes, capacity - position);
		ret = capacity - position;		
		size = capacity;
		position = capacity;
	}
	else
	{
		memcpy((void *)(&(buffer[position])), bytes, amountToWrite);
		if(size < position + amountToWrite)
		{
			size = position + amountToWrite;
		}
		position += amountToWrite;
		ret = amountToWrite;
	}
	return ret;
}
unsigned int memPage_t::write(const unsigned int pos, const void* bytes, unsigned int amountToWrite)
{
	if(pos > size)
	{
		cout << "Invalid position!\n";
		return 0;
	}
	position = pos;
	return write(bytes, amountToWrite);
}