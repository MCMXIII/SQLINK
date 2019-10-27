#include <fstream>
#include <iostream>
#include <string>
#include <deque>
#include <utility>
#include "tokenizer_t.h"
#include "analyzer_t.h"
#ifndef PARSER_T_H
#define PARSER_T_H

using namespace std;

class parser_t{
	public:
		parser_t() { lineNumber = 1; tokenizer = new tokenizer_t(); analyzer = new analyzer_t(); }
		void openFile(const string& name) { if(!stream.is_open()) { stream.open(name.c_str(), std::fstream::in); if(stream.good()) fileName = name; else fileName = string("*"); }}
		void closeFile() { if(stream.is_open()) stream.close(); }
		void parse(const string& name);
		~parser_t() { closeFile(); delete tokenizer; delete analyzer; }
	private:
		unsigned int lineNumber;
		string fileName;
		fstream stream;
		tokenizer_t* tokenizer;
		analyzer_t* analyzer;
		deque<pair<int, string> > tokens;
		parser_t(const parser_t& other) {}
		parser_t& operator=(const parser_t& other);
};

#endif
