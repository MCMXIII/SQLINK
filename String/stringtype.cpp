#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringtype.h"

static int num = 0;
stringType::stringType()
{
	size = 0;
	str = 0;
	num++;
}
stringType::stringType(const char* source)
{
	size = strlen(source);
	str = new char[size+1];
	strcpy(str, source);
	str[size] = '\0';
	num++;
}
stringType::stringType(const stringType& other)
{
	size = other.size;
	str = new char[size+1];
	strcpy(str, other.str);
	str[size] = '\0';
	num++;
}
stringType::~stringType()
{
	delete [] str;
	num--;
}
stringType& stringType::operator=(const stringType& other)
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
stringType& stringType::operator+=(const stringType other)
{
	char* oldString = new char[size+1];
	strcpy(oldString, str);
	delete [] str;
	size += other.size;
	str = new char[size+1];
	strcpy(str, oldString);
	strcat(str, other.str);
	return *this;
}
stringType& stringType::operator+=(const char* other)
{
	char* oldString = new char[size+1];
	strcpy(oldString, str);
	delete [] str;
	size += strlen(other);
	str = new char[size+1];
	strcpy(str, oldString);
	strcat(str, other);
	return *this;
}
int stringType::operator<(const stringType other)
{
	return strcmp(str, other.str) < 0;
}
int stringType::operator>(const stringType other)
{
	return strcmp(str, other.str) > 0;
}
int stringType::operator<=(const stringType other)
{
	return strcmp(str, other.str) <= 0;
}
int stringType::operator>=(const stringType other)
{
	return strcmp(str, other.str) >= 0;
}
int stringType::operator==(const stringType other)
{
	return strcmp(str, other.str) == 0;
}
int stringType::operator!=(const stringType other)
{
	return strcmp(str, other.str) != 0;
}
int stringType::operator<(const char* other)
{
	return strcmp(str, other) < 0;
}
int stringType::operator>(const char* other)
{
	return strcmp(str, other) > 0;
}
int stringType::operator<=(const char* other)
{
	return strcmp(str, other) <= 0;
}
int stringType::operator>=(const char* other)
{
	return strcmp(str, other) >= 0;
}
int stringType::operator==(const char* other)
{
	return strcmp(str, other) == 0;
}
int stringType::operator!=(const char* other)
{
	return strcmp(str, other) != 0;
}
char& stringType::operator[](int index)
{
	if (index >= size || index < 0)
	{
		cout << "String index out of bound, exiting.\n";
		exit(0);
	}
	return str[index];
}
int stringType::length() const
{
	return size;
}
void stringType::setString(char* newString)
{
	delete [] str;
	size = strlen(newString);
	str = new char[size+1];
	strcpy(str, newString);
	str[size] = '\0';
	
}
const char* stringType::getString() const
{
	return str;
}
int stringType::compare(const stringType other) const
{
	return strcmp(str, other.str);
}
void stringType::print() const
{
	/*printf("%s\n", str);*/
	cout << *this << "\n";
}
void stringType::toUpper()
{
	int i;
	for(i = 0; i < size; i++)
	{
		if(str[i] >= 'a' && str[i] <= 'z')
		{
			str[i]+=('A' - 'a');
		}
	}
}
void stringType::toLower()
{
	int i;
	for(i = 0; i < size; i++)
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i]+=('a' - 'A');
		}
	}
}
void stringType::prepend(const stringType first)
{
	char* oldString = new char[size+1];
	strcpy(oldString, str);
	delete [] str;
	size += first.size;
	str = new char[size+1];
	strcpy(str, first.str);
	strcpy(&(str[first.size]), oldString);
}
void stringType::prepend(const char* first)
{
	char* oldString = new char[size+1];
	strcpy(oldString, str);
	delete [] str;
	size += strlen(first);
	str = new char[size+1];
	strcpy(str, first);
	strcpy(&(str[strlen(first)]), oldString);
}
int stringType::contains(const stringType sub) const
{
	int i = 0, j = 0;
	for(i = 0; i <= size - sub.size; i++)
	{
		j = 0;
		while(str[i+j] == sub.str[j] && str[i+j] != '\0')
		{
			j++;
		}
		if(sub.str[j] == '\0')
		{
			return 1;
		}
	}
	return 0;
}
int stringType::contains(const char* sub) const
{
	int i = 0, j = 0;
	for(i = 0; i <= size - strlen(sub); i++)
	{
		j = 0;
		while(str[i+j] == sub[j] && str[i+j] != '\0')
		{
			j++;
		}
		if(sub[j] == '\0')
		{
			return 1;
		}
	}
	return 0;
}
int stringType::countStrings()
{
	return num;
}
std::ostream& operator<<(std::ostream& os, const stringType& s)
{
	os << s.getString();
	return os;
}
std::istream& operator>>(std::istream& is, stringType& s)
{
	char st[128];
	is >> st;
	s.setString(st);
	return is;
}