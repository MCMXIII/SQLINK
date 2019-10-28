#ifndef TOKENIZER_T_H
#define TOKENIZER_T_H

#include <fstream>
#include <string>
#include <deque>
#include <sstream>

using std::string;
using std::deque;
using std::stringstream;

class tokenizer_t{
	public:
		tokenizer_t() {}
		~tokenizer_t() {}
		void tokenize(const string& line, deque<string>& tokens);
	private:
		tokenizer_t(const tokenizer_t& other) {}
		tokenizer_t& operator=(const tokenizer_t& other);
		static string delimiters;
};

#endif
