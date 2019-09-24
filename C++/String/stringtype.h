#include <iostream>
#ifndef STRINGTYPE_H
#define STRINGTYPE_H

using namespace std;
class stringType
{
	public:
		stringType();
		stringType(const char* source);
		stringType(const stringType& other);
		~stringType();
		stringType& operator=(const stringType& other);
		stringType& operator+=(const stringType other);
		stringType& operator+=(const char* other);
		int operator<(const stringType other);
		int operator>(const stringType other);
		int operator<=(const stringType other);
		int operator>=(const stringType other);
		int operator==(const stringType other);
		int operator!=(const stringType other);
		int operator<(const char* other);
		int operator>(const char* other);
		int operator<=(const char* other);
		int operator>=(const char* other);
		int operator==(const char* other);
		int operator!=(const char* other);
		char& operator[](int index);
		stringType operator()(int index, unsigned int length);
		int length() const { return size; }
		void setString(char* newString);
		const char* getString() const { return str; }
		int compare(const stringType other) const;
		void print() const;
		void toUpper();
		void toLower();
		void prepend(const stringType first);
		void prepend(const char* first);
		int contains(const stringType sub) const;
		int contains(const char* sub) const;
		int firstIndex(const char c) const;
		int lastIndex(const char c) const;
		static int countStrings();
		static int getCaseSens();
		static int setCaseSens();
		static int setCaseSens(int newSensitivity);
		static int getCapacity();
		static int setCapacity(int newCapacity);
	private:
		static int number;
		static int caseSens;
		static size_t capacity;
		char* str;
		int size;
};
	ostream& operator<<(ostream& os, const stringType& s);
	istream& operator>>(istream& is, stringType& s);
#endif
