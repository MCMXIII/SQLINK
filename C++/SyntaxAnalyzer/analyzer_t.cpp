#include <fstream>
#include <ctype.h>
#include <iostream>
#include <string>
#include <string.h>
#include <deque>
#include <vector>
#include "analyzer_t.h"

string* analyzer_t::types = new string[7];
string* analyzer_t::keywords = new string[11];
string analyzer_t::nsDelimiters = "()[]{};<>=+-*&";

using namespace std;
		
void find3InARow(int& counter, const string& fileName, const string& token, const char& oper)
{
	if(token[0] == oper)
	{
		counter++;
		if(counter >= 3)
		{
			cout << fileName << ':' << token << " - error, no operator +++ or ---" << endl;
		}
	}
	else
	{
		counter = 0;
	}
}
void findUnordered(int& counter, const string& fileName, const int& lineNum, const char& opening)
{
	char closing;
	switch(opening)
	{
		case '(':	closing = ')'; break;
		case '{':	closing = '}'; break;
		case '[':	closing = ']'; break;
		default: break;
	}
	counter--;
	if(counter < 0) 
	{
		cout << fileName << ':' << lineNum << " - error, \"" << closing << "\" without \"" << opening << "\"" << endl;
		counter = 0;
	}
}

void analyzer_t::init(const string& name)
{
	typeFlag = false;
	afterMain = false;
	notFoundMain = false;
	declareKeywords();
	fileName = name;
	declared = new vector<string>();
}
void analyzer_t::analyze(deque<string>& tokens)
{
	if(tokens.size() == 0)
	{
		line++;
		return;
	}
	if(!afterMain && !notFoundMain && tokens[0] != "main")
	{
		cout << fileName << ':' << line << " - error, illegal - no 'main' before" << endl;
		notFoundMain = true;
	}
	while(tokens.size() > 0)
	{
		string token = tokens[0];
		tokens.pop_front();
		if(token == "main" && afterMain == false)
		{
			(*declared).push_back(token);
			afterMain = true;
			continue;
		}
		doIfBracket(token);
		find3InARow(plusCounter, fileName, token, '+');
		find3InARow(minusCounter, fileName, token, '-');
		if(token == "if" || token == "else")
		{
			checkIfElse(token);
			continue;
		}
		if(isType(token) && !typeFlag)
		{
			typeFlag = true;
			continue;
		}
		checkTokenValue(typeFlag, token);
	}
	line++;
}
void analyzer_t::finish()
{
	checkBracketsFinally();
	cleanAll();
}

void analyzer_t::declareKeywords()
{
	string typesArr[7] = {"char", "short", "int", "long", "float", "double", "void"};
	string keywordsArr[11] = {"if", "else", "for", "while", "class", "private", "public", "protected", "main", "const", "virtual"};
	for(int i = 0; i < 7; i++)
	{
		analyzer_t::types[i] = typesArr[i];
		analyzer_t::keywords[i] = keywordsArr[i];
	}
	for(int i = 7; i < 11; i++)
	{
		analyzer_t::keywords[i] = keywordsArr[i];
	}
}
void analyzer_t::doIfBracket(const string& token)
{
	switch(token[0])
	{
		case '(': parentheses++;
				break;
		case ')': findUnordered(parentheses, fileName, line, '(');
				break;
		case '{': braces++;
				break;
		case '}': findUnordered(braces, fileName, line, '{');
				break;
		case '[': brackets++;
				break;
		case ']': findUnordered(brackets, fileName, line, '[');
				break;
		default: break;			
	}
		
}
void analyzer_t::checkIfElse(const string& token)
{
	if(token == "if")
	{
		ifCounter++;
	}
	if(token == "else")
	{
		ifCounter--;
		if(ifCounter < 0)
		{
			cout << fileName << ':' << line << " - error, \"else\" without \"if\"" << endl;
			ifCounter = 0;
		}
	}
}
void analyzer_t::checkTokenValue(bool& isAfterType, const string& token)
{
	if(isAfterType)
	{
		isAfterType = false;			
		if(isLegalVarName(token, line))
		{
			if(isDeclared(token))
			{
				cout << fileName << ':' << line << " - error, variable '" << token << "' already declared" << endl;
			}
			else
			{
				(*declared).push_back(token);
			}
		}
	}
	else if(strchr(analyzer_t::nsDelimiters.c_str(), token[0]) == 0)
	{
		bool isNumeric = true;
		for(int i = 0; i < token.length(); i++)
		{
			if(!isdigit(token[i])) isNumeric = false;
		}
		if(!isNumeric && !isDeclared(token) && !isKeyword(token))
		{
			cout << fileName << ':' << line << " - error, '" << token << "' is not declared" << endl;
		}
	}
}
void analyzer_t::checkBracketsFinally()
{
	if(parentheses > 0) cout << fileName << " - error, " << parentheses << " '(' not closed" << endl;
	if(brackets > 0) cout << fileName << " - error, " << brackets << " '[' not closed" << endl;
	if(braces > 0) cout << fileName << " - error, " << braces << " '{' not closed" << endl;
}
void analyzer_t::cleanAll()
{
	line = 1; parentheses = 0; braces = 0; brackets = 0; plusCounter = 0; minusCounter = 0; ifCounter = 0; (*declared).clear();
}
bool analyzer_t::isType(const string& token)
{
	for(int i = 0; i < 7; i++)
	{
		if(token == analyzer_t::types[i])
			return true;
	}
	return false;
}
bool analyzer_t::isKeyword(const string& token)
{
	for(int i = 0; i < 11; i++)
	{
		if(token == analyzer_t::keywords[i])
			return true;
	}
	return false;

}
bool analyzer_t::isLegalVarName(const string& token, int lineNum)
{
	if(!isalpha(token[0]) || isKeyword(token))
	{
		cout << fileName << ':' << lineNum << " - error, illegal variable name" << endl;
		return false;
	}
	for(int i = 1; i < token.length(); i++)
	{
		if(!isalnum(token[i]))
		{
			cout << fileName << ':' << lineNum << " - error, illegal variable name" << endl;
			return false;
		}
	}
	if(isType(token))
	{
		cout << fileName << ':' << lineNum << " - error, multiple type declaration" << endl;
		return false;
	}
	return true;
}
bool analyzer_t::isDeclared(const string& token)
{
	vector<string>::iterator it = (*declared).begin();
	while(it != (*declared).end())
	{
		if(token == *it++)
			return true;
	}
	return false;
}