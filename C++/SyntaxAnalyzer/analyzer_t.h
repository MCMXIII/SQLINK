#include <fstream>
#include <string>
#include <deque>
#include <utility>
#include <vector>
#ifndef ANALYZER_T_H
#define ANALYZER_T_H

using namespace std;

class analyzer_t{
	public:
		analyzer_t() { parentheses = 0; braces = 0; brackets = 0; plusCounter = 0; minusCounter = 0; ifCounter = 0; }
		void analyze(const string& fileName, deque<pair<int, string> >& tokens);
	private:
		int parentheses;
		int braces;
		int brackets;
		int plusCounter;
		int minusCounter;
		int ifCounter;
		vector<string> declared;
		bool isType(const string& token);
		bool isKeyword(const string& token);
		bool isLegalVarName(const string& token, const string& fileName, int line);
		bool isDeclared(const string& token);
		
};



#endif