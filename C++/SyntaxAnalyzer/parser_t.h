#include <fstream>
#include <string>
#ifndef PARSER_T_H
#define PARSER_T_H

using namespace std;

class parser_t{
	public:
		parser_t() { lineNumber = 0; }
		parser_t(const string& name) { lineNumber = 0; stream.open(name.c_str(), std::fstream::in); if(stream.good()) fileName = name; }
		void openFile(const string& name) { if(!stream.is_open()) { stream.open(name.c_str(), std::fstream::in); if(stream.good()) fileName = name; } }
		void closeFile() { if(stream.is_open()) stream.close(); }
		void getLine() {}
		~parser_t() { if(stream.is_open()) stream.close(); }
	private:
		unsigned int lineNumber;
		string fileName;
		fstream stream;
		parser_t(const parser_t& other) {}
		parser_t& operator=(const parser_t& other);

};

#endif