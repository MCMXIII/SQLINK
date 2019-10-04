#include <string>
#ifndef TEXCEPTION_T_H
#define TEXCEPTION_T_H

using namespace std;
template <class T> class TException_t
{
	public:
		TException_t(T o, string desc, string f, unsigned int l) { obj = o; description = desc; file = f; line = l; }
		~TException_t() {}
		T getObject() { return obj; }
		string getDescription() { return description; }
		string getFileName() { return file; }
		unsigned int getLine() { return line; }
	private:
		T obj;
		string description;
		string file;
		unsigned int line;
};

#endif