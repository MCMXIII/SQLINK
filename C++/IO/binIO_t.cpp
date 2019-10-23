#include "binIO_t.h"
#include <stdio.h>
#include <string>

binIO_t& binIO_t::operator<<(const int value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fwrite((void*)&value, sizeof(int), 1, fp) <= 1)
	{
		setStatus(writeErr_e);
		throw(string("Cannot write to file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator<<(const char value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fwrite((void*)&value, sizeof(char), 1, fp) <= 1)
	{
		setStatus(writeErr_e);
		throw(string("Cannot write to file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator<<(const short value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fwrite((void*)&value, sizeof(short), 1, fp) <= 1)
	{
		setStatus(writeErr_e);
		throw(string("Cannot write to file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator<<(const long value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fwrite((void*)&value, sizeof(long), 1, fp) <= 1)
	{
		setStatus(writeErr_e);
		throw(string("Cannot write to file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator<<(const unsigned int value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fwrite((void*)&value, sizeof(unsigned int), 1, fp) <= 1)
	{
		setStatus(writeErr_e);
		throw(string("Cannot write to file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator<<(const unsigned char value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fwrite((void*)&value, sizeof(unsigned char), 1, fp) <= 1)
	{
		setStatus(writeErr_e);
		throw(string("Cannot write to file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator<<(const unsigned short value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fwrite((void*)&value, sizeof(unsigned short), 1, fp) <= 1)
	{
		setStatus(writeErr_e);
		throw(string("Cannot write to file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator<<(const unsigned long value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fwrite((void*)&value, sizeof(unsigned long), 1, fp) <= 1)
	{
		setStatus(writeErr_e);
		throw(string("Cannot write to file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator<<(const float value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fwrite((void*)&value, sizeof(float), 1, fp) <= 1)
	{
		setStatus(writeErr_e);
		throw(string("Cannot write to file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator<<(const double value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fwrite((void*)&value, sizeof(double), 1, fp) <= 1)
	{
		setStatus(writeErr_e);
		throw(string("Cannot write to file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator<<(const void* buf)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+'))
	{
		setStatus(writeErr_e);
		throw(string("Cannot write to file!"));
	}
	else
	{
		isRead = false;
		rwBuffer = (void*)buf;
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator>>(int& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fread((void*)&value, sizeof(int), 1, fp) <= 1)
	{
		setStatus(readErr_e);
		throw(string("Cannot read from file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator>>(char& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fread((void*)&value, sizeof(char), 1, fp) <= 1)
	{
		setStatus(readErr_e);
		throw(string("Cannot read from file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator>>(short& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fread((void*)&value, sizeof(short), 1, fp) <= 1)
	{
		setStatus(readErr_e);
		throw(string("Cannot read from file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator>>(long& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fread((void*)&value, sizeof(long), 1, fp) <= 1)
	{
		setStatus(readErr_e);
		throw(string("Cannot read from file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator>>(unsigned int& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fread((void*)&value, sizeof(unsigned int), 1, fp) <= 1)
	{
		setStatus(readErr_e);
		throw(string("Cannot read from file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator>>(unsigned char& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fread((void*)&value, sizeof(unsigned char), 1, fp) <= 1)
	{
		setStatus(readErr_e);
		throw(string("Cannot read from file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator>>(unsigned short& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fread((void*)&value, sizeof(unsigned short), 1, fp) <= 1)
	{
		setStatus(readErr_e);
		throw(string("Cannot read from file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator>>(unsigned long& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fread((void*)&value, sizeof(unsigned long), 1, fp) <= 1)
	{
		setStatus(readErr_e);
		throw(string("Cannot read from file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator>>(float& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fread((void*)&value, sizeof(float), 1, fp) <= 1)
	{
		setStatus(readErr_e);
		throw(string("Cannot read from file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator>>(double& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fread((void*)&value, sizeof(double), 1, fp) <= 1)
	{
		setStatus(readErr_e);
		throw(string("Cannot read from file!"));
	}
	else
	{
		setStatus(ok_e);
	}
	return *this;
}
binIO_t& binIO_t::operator>>(void* buf)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+'))
	{
		setStatus(writeErr_e);
		throw(string("Cannot read from file!"));
	}
	else
	{
		isRead = true;
		rwBuffer = buf;
		setStatus(ok_e);
	}
	return *this;
}
void binIO_t::operator,(int len)
{
	if(isRead)
	{
		fread(rwBuffer, len, 1, fp);
	}
	else
	{
		fwrite(rwBuffer, len, 1, fp);
	}
	rwBuffer = 0;
}