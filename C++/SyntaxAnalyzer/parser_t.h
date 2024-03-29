#ifndef PARSER_T_H
#define PARSER_T_H

#include <iostream>
#include <fstream>
#include <string>
#include <deque>

class analyzer_t;
class tokenizer_t;

using std::fstream;
using std::string;
using std::deque;
using std::endl;
using std::cout;

class parser_t{
	public:
		parser_t();
		void openFile(const string& name) { if(!stream.is_open()) { stream.open(name.c_str(), std::fstream::in); if(stream.good()) fileName = name; else fileName = string("*"); }}
		void closeFile() { if(stream.is_open()) stream.close(); }
		void parse(const string& name);
		~parser_t();
	private:
		string fileName;
		fstream stream;
		tokenizer_t* tokenizer;
		analyzer_t* analyzer;
		deque<string> tokens;
		parser_t(const parser_t& other) {}
		parser_t& operator=(const parser_t& other);
};

#endif
