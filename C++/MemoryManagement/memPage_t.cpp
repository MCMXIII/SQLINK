#include "memPage_t.h"
#include <string.h>

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
	return (char*)output;
}
char* memPage_t::read(void* output, const unsigned int pos, unsigned int bytes)
{
	if(output != 0 && pos <= size)
	{
		position = pos;
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
	return (char*)output;
}
unsigned int memPage_t::write(const char* bytes)
{
	int ret;
	if(position + strlen(bytes) > capacity)
	{
		memcpy((void *)(&(buffer[position])), (void *)bytes, capacity - position);
		ret = capacity - position;		
		size = capacity;
		position = capacity;
	}
	else
	{
		memcpy((void *)(&(buffer[position])), (void *)bytes, strlen(bytes));
		if(size < position + strlen(bytes))
		{
			size = position + strlen(bytes);
		}
		position += strlen(bytes);
		ret = strlen(bytes);
	}
	return ret;
}
unsigned int memPage_t::write(const unsigned int pos, const char* bytes)
{
	if(pos > size)
	{
		return 0;
	}
	int ret;
	position = pos;
	if(position + strlen(bytes) > capacity)
	{
		memcpy((void *)(&(buffer[position])), (void *)bytes, capacity - position);
		ret = capacity - position;		
		size = capacity;
		position = capacity;
	}
	else
	{
		memcpy((void *)(&(buffer[position])), (void *)bytes, strlen(bytes));
		if(size < position + strlen(bytes))
		{
			size = position + strlen(bytes);
		}
		position += strlen(bytes);
		ret = strlen(bytes);
	}
	return ret;
}