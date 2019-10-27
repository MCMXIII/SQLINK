#ifndef ANALYZER_T_H
#define ANALYZER_T_H

#include <fstream>
#include <string>
#include <deque>
#include <vector>

using namespace std;

class analyzer_t{
	public:
		analyzer_t() { line = 1; parentheses = 0; braces = 0; brackets = 0; plusCounter = 0; minusCounter = 0; ifCounter = 0; }
		~analyzer_t() { /*delete declared;*/ }
		void init(const string& name);
		void analyze(deque<string>& tokens);
		void finish();
	private:
		int parentheses;
		int braces;
		int brackets;
		int plusCounter;
		int minusCounter;
		int ifCounter;
		int line;
		bool typeFlag;
		bool afterMain;
		bool notFoundMain;
		string fileName;
		static string* types;
		static string* keywords;
		static string nsDelimiters;
		vector<string>* declared;
		void declareKeywords();
		void doIfBracket(const string& token);
		void checkIfElse(const string& token);
		void checkTokenValue(bool& isAfterType, const string& token);
		void checkBracketsFinally();
		void cleanAll();
		bool isType(const string& token);
		bool isKeyword(const string& token);
		bool isLegalVarName(const string& token, int line);
		bool isDeclared(const string& token);
		
};



#endif
