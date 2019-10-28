#ifndef ANALYZER_T_H
#define ANALYZER_T_H

#include <fstream>
#include <string>
#include <deque>
#include <vector>

using std::fstream;
using std::string;
using std::deque;
using std::vector;

class analyzer_t{
	public:
		analyzer_t() { line = 1; parentheses = 0; braces = 0; brackets = 0; plusCounter = 0; minusCounter = 0; ifCounter = 0; }
		virtual ~analyzer_t() {}
		virtual void init(const string& name);
		virtual void analyze(deque<string>& tokens);
		virtual void finish();
	protected:
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
		vector<string>* declared;
		static string* types;
		static string* keywords;
		static string nsDelimiters;
		virtual void declareKeywords();
		void findUnordered(const int& lineNum, const char& opening);
		void doIfBracket(const string& token);
		void find3InARow(const int& lineNum, const string& token, const char& oper);
		void checkIfElse(const string& token);
		void checkTokenValue(bool& isAfterType, const string& token);
		void checkBracketsFinally() const;
		virtual void cleanAll();
		bool isType(const string& token) const;
		bool isKeyword(const string& token) const;
		bool isLegalVarName(const string& token, const int& line) const;
		bool isDeclared(const string& token) const;
	private:
		analyzer_t(const analyzer_t& other) {}
		analyzer_t& operator=(const analyzer_t& other);
		
};



#endif
