#include "asciiIO_t.h"
#include <stdio.h>
#include <string>

asciiIO_t& asciiIO_t::operator<<(const int value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+')  || fprintf(fp, "%d", value) <= 0)
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
asciiIO_t& asciiIO_t::operator<<(const char value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fprintf(fp, "%c", value) <= 0)
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
asciiIO_t& asciiIO_t::operator<<(const short value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fprintf(fp, "%hd", value) <= 0)
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
asciiIO_t& asciiIO_t::operator<<(const long value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fprintf(fp, "%ld", value) <= 0)
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
asciiIO_t& asciiIO_t::operator<<(const unsigned int value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fprintf(fp, "%u", value) <= 0)
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
asciiIO_t& asciiIO_t::operator<<(const unsigned char value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fprintf(fp, "%u", value) <= 0)
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
asciiIO_t& asciiIO_t::operator<<(const unsigned short value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fprintf(fp, "%hu", value) <= 0)
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
asciiIO_t& asciiIO_t::operator<<(const unsigned long value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fprintf(fp, "%lu", value) <= 0)
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
asciiIO_t& asciiIO_t::operator<<(const float value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fprintf(fp, "%f", value) <= 0)
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
asciiIO_t& asciiIO_t::operator<<(const double value)
{
	if(fp == 0 || (accessMode[0] != 'w' && accessMode[1] != '+') || fprintf(fp, "%f", value) <= 0)
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
asciiIO_t& asciiIO_t::operator>>(int& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fscanf(fp, "%d", &value) <= 0)
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
asciiIO_t& asciiIO_t::operator>>(char& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fscanf(fp, "%c", &value) <= 0)
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
asciiIO_t& asciiIO_t::operator>>(short& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fscanf(fp, "%hd", &value) <= 0)
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
asciiIO_t& asciiIO_t::operator>>(long& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fscanf(fp, "%ld", &value) <= 0)
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
asciiIO_t& asciiIO_t::operator>>(unsigned int& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fscanf(fp, "%u", &value) <= 0)
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
asciiIO_t& asciiIO_t::operator>>(unsigned char& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fscanf(fp, "%u", (unsigned int*)&value) <= 0)
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
asciiIO_t& asciiIO_t::operator>>(unsigned short& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fscanf(fp, "%hu", &value) <= 0)
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
asciiIO_t& asciiIO_t::operator>>(unsigned long& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fscanf(fp, "%lu", &value) <= 0)
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
asciiIO_t& asciiIO_t::operator>>(float& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fscanf(fp, "%f", &value) <= 0)
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
asciiIO_t& asciiIO_t::operator>>(double& value)
{
	if(fp == 0 || (accessMode[0] != 'r' && accessMode[1] != '+')  || fscanf(fp, "%f", (float*)&value) <= 0)
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