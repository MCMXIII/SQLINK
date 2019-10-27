#ifndef ANALYZER_T_H
#define ANALYZER_T_H

#include <fstream>
#include <string>
#include <deque>
#include <utility>
#include <vector>

using namespace std;

class analyzer_t{
	public:
		analyzer_t() { parentheses = 0; braces = 0; brackets = 0; plusCounter = 0; minusCounter = 0; ifCounter = 0; }
		~analyzer_t() { /*delete declared;*/ }
		void analyze(const string& name, deque<pair<int, string> >& tokens);
	private:
		int parentheses;
		int braces;
		int brackets;
		int plusCounter;
		int minusCounter;
		int ifCounter;
		string fileName;
		static string* types;
		static string* keywords;
		static string nsDelimiters;
		vector<string>* declared;
		void declareKeywords();
		void doIfBracket(const pair<int, string>& token);
		void checkIfElse(const pair<int, string>& token);
		void checkTokenValue(bool& isAfterType, const pair<int, string>& token);
		void checkBracketsFinally();
		void cleanAll();
		bool isType(const string& token);
		bool isKeyword(const string& token);
		bool isLegalVarName(const string& token, int line);
		bool isDeclared(const string& token);
		
};



#endif
