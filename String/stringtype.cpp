#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringtype.h"

string::string()
{
	size = 0;
	str = 0;
}
string::string(const char* source)
{
	size = strlen(source);
	str = new char[size+1];
	strcpy(str, source);
	str[size] = '\0';
}
string::string(const string& other)
{
	size = other.size;
	str = new char[size+1];
	strcpy(str, other.str);
	str[size] = '\0';
}
string::~string()
{
	delete [] str;
}
string& string::operator=(const string& other)
{
	if(this != & other)
	{
		delete [] str;
		size = other.size;
		str = new char[size+1];
		strcpy(str, other.str);
		str[size] = '\0';
	}
	return *this;
}
int string::length() const
{
	return size;
}
void string::setString(char* newString)
{
	delete [] str;
	size = strlen(newString);
	str = new char[size+1];
	strcpy(str, newString);
	str[size] = '\0';
	
}
const char* string::getString() const
{
	return str;
}
int string::compare(const string other) const
{
	return strcmp(str, other.str);
}
void string::print() const
{
	printf("%s\n", str);
}