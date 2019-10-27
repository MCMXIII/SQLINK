#ifndef TOKENIZER_T_H
#define TOKENIZER_T_H

#include <fstream>
#include <string>
#include <deque>
#include <sstream>

using namespace std;

class tokenizer_t{
	public:
		tokenizer_t() {}
		~tokenizer_t() {}
		void tokenize(const string& line, const int& lineNum, deque<pair<int, string> >& tokens);
	private:
		tokenizer_t(const tokenizer_t& other) {}
		tokenizer_t& operator=(const tokenizer_t& other);
		static string delimiters;
};

#endif
