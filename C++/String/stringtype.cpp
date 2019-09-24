#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "stringtype.h"

int stringType::number = 0;
int stringType::caseSens = 1;
size_t stringType::capacity = 1;
stringType::stringType()
{
	size = 0;
	str = 0;
	if(number == 0)
	{
		stringType::capacity = 8;
	}
	stringType::number++;
}
stringType::stringType(const char* source)
{
	if(source == 0)
	{
		stringType();
	}
	else
	{
		size = strlen(source);
		if(stringType::capacity <= size)
		{
			for(; stringType::capacity <= size; stringType::capacity*=2){}
		}
		str = new char[stringType::capacity];
		strcpy(str, source);
		str[size] = '\0';
		stringType::number++;
	}
}
stringType::stringType(const stringType& other)
{
	if(other.str == 0)
	{
		stringType();
	}
	else
	{
		size = other.size;
		str = new char[stringType::capacity];
		strcpy(str, other.str);
		str[size] = '\0';
		stringType::number++;
	}
}
stringType::~stringType()
{
	delete [] str;
	stringType::number--;
}
stringType& stringType::operator=(const stringType& other)
{
	if(this != & other && other.str != 0)
	{
		delete [] str;
		size = other.size;
		str = new char[stringType::capacity];
		strcpy(str, other.str);
		str[size] = '\0';
	}
	return *this;
}
stringType& stringType::operator+=(const stringType other)
{
	if(other.str == 0)
	{
		return *this;
	}
	char* oldString = new char[size+1];
	strcpy(oldString, str);
	delete [] str;
	size += other.size;
	if(stringType::capacity <= size)
	{
		for(; stringType::capacity <= size; stringType::capacity*=2){}
	}
	str = new char[stringType::capacity];
	strcpy(str, oldString);
	strcat(str, other.str);
	return *this;
}
stringType& stringType::operator+=(const char* other)
{
	if(other == 0)
	{
		return *this;
	}
	char* oldString = new char[size+1];
	strcpy(oldString, str);
	delete [] str;
	size += strlen(other);
	if(stringType::capacity <= size)
	{
		for(; stringType::capacity <= size; stringType::capacity*=2){}
	}
	str = new char[stringType::capacity];
	strcpy(str, oldString);
	strcat(str, other);
	return *this;
}
int stringType::operator<(const stringType other)
{
	return (this==0||this->str==0||other.str==0)?-256:((*this).compare(other) < 0);
}
int stringType::operator>(const stringType other)
{
	return (this==0||this->str==0||other.str==0)?-256:((*this).compare(other) > 0);
}
int stringType::operator<=(const stringType other)
{
	return (this==0||this->str==0||other.str==0)?-256:((*this).compare(other) <= 0);
}
int stringType::operator>=(const stringType other)
{
	return (this==0||this->str==0||other.str==0)?-256:((*this).compare(other) >= 0);
}
int stringType::operator==(const stringType other)
{
	return (this==0||this->str==0||other.str==0)?-256:((*this).compare(other) == 0);
}
int stringType::operator!=(const stringType other)
{
	return (this==0||this->str==0||other.str==0)?-256:((*this).compare(other) != 0);
}
int compareIgnoreCase(const char* s1, const char*  s2)
{
	if(s1 == 0 || s2 == 0)
	{
		return -256;
	}
	int i;
	while(toupper(s1[i]) == toupper(s2[i]) && s1[i] != '\0')
	{
		i++;
	}
	return s1[i] - s2[i];
}
int stringType::operator<(const char* other)
{
	return (this==0||this->str==0||other==0)?-256:((caseSens?strcmp(str, other):compareIgnoreCase(str, other)) < 0);
}
int stringType::operator>(const char* other)
{
	return (this==0||this->str==0||other==0)?-256:((caseSens?strcmp(str, other):compareIgnoreCase(str, other)) > 0);
}
int stringType::operator<=(const char* other)
{
	return (this==0||this->str==0||other==0)?-256:((caseSens?strcmp(str, other):compareIgnoreCase(str, other)) <= 0);
}
int stringType::operator>=(const char* other)
{
	return (this==0||this->str==0||other==0)?-256:((caseSens?strcmp(str, other):compareIgnoreCase(str, other)) >= 0);
}
int stringType::operator==(const char* other)
{
	return (this==0||this->str==0||other==0)?-256:((caseSens?strcmp(str, other):compareIgnoreCase(str, other)) == 0);
}
int stringType::operator!=(const char* other)
{
	return (this==0||this->str==0||other==0)?-256:((caseSens?strcmp(str, other):compareIgnoreCase(str, other)) != 0);
}
char& stringType::operator[](int index)
{
	if (index >= size || index < 0)
	{
		char c = '\0';
		char& cr = c;
		return cr;
	}
	return str[index];
}
stringType stringType::operator()(int index, unsigned int length)
{
	if (index >= size || index < 0)
	{
		stringType st;
		return st;
	}
	char* subStr = new char[length+1];
	strncpy(subStr, &(str[index]), length);
	subStr[length] = '\0';
	stringType st(subStr);
	return st;
}
void stringType::setString(char* newString)
{
	if(newString != 0)
	{
		delete [] str;
		size = strlen(newString);
		if(stringType::capacity <= size)
		{
			for(; stringType::capacity <= size; stringType::capacity*=2){}
		}
		str = new char[stringType::capacity];
		strcpy(str, newString);
		str[size] = '\0';
	}
}
int stringType::compare(const stringType other) const
{
	if(caseSens)
	{
		return strcmp(str, other.str);
	}
	stringType s1((*this));
	stringType s2(other);
	s1.toUpper();
	s2.toUpper();
	return strcmp(s1.str, s2.str);
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
	if(stringType::capacity <= size)
	{
		for(; stringType::capacity <= size; stringType::capacity*=2){}
	}
	str = new char[stringType::capacity];
	strcpy(str, first.str);
	strcpy(&(str[first.size]), oldString);
}
void stringType::prepend(const char* first)
{
	char* oldString = new char[size+1];
	strcpy(oldString, str);
	delete [] str;
	size += strlen(first);
	if(stringType::capacity <= size)
	{
		for(; stringType::capacity <= size; stringType::capacity*=2){}
	}
	str = new char[stringType::capacity];
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
int stringType::firstIndex(const char c) const
{
	int i = 0;
	if(caseSens)
	{
		for(i = 0; i < size; i++)
		{
			if(str[i] == c)
			{
				break;
			}
		}
	}
	else
	{
		for(i = 0; i < size; i++)
		{
			if(toupper(str[i]) == toupper(c))
			{
				break;
			}
		}
	}
	return i;
}
int stringType::lastIndex(const char c) const
{
	int i = 0, lIndex = -1;
	if(caseSens)
	{
		for(i = 0; i < size; i++)
		{
			if(str[i] == c)
			{
				lIndex = i;
			}
		}
	}
	else
	{
		for(i = 0; i < size; i++)
		{
			if(toupper(str[i]) == toupper(c))
			{
				lIndex = i;
			}
		}
	}
	if (lIndex == -1)
	{
		lIndex = i;
	}
	return lIndex;
}
int stringType::countStrings()
{
	return stringType::number;
}
int stringType::getCaseSens()
{
	return stringType::caseSens;
}
int stringType::setCaseSens()
{
	stringType::caseSens = (stringType::caseSens + 1) % 2;
	return (stringType::caseSens + 1) % 2;
}
int stringType::getCapacity()
{
	return stringType::capacity;
}
int stringType::setCapacity(int newCapacity)
{
	int old = capacity;
	for(; capacity < newCapacity; capacity*=2);
	return old;
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