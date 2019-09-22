#ifndef STRINGTYPE_H
#define STRINGTYPE_H

class string
{
	public:
		string();
		string(const char* source);
		string(const string& other);
		~string();
		string& operator=(const string& other);
		int length() const;
		void setString(char* newString);
		const char* getString() const;
		int compare(const string other) const;
		void print() const;
	private:
		char* str;
		int size;
};

#endif
