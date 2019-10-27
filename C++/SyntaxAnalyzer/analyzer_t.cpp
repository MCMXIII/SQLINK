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
		
void find3InARow(int& counter, const string& fileName, const pair<int, string>& token, const char& oper)
{
	if(token.second[0] == oper)
	{
		counter++;
		if(counter >= 3)
		{
			cout << fileName << ':' << token.first << " - error, no operator +++ or ---" << endl;
		}
	}
	else
	{
		counter = 0;
	}
}
void findUnordered(int& counter, const string& fileName, const int& row, const char& opening)
{
	char closing;
	switch(opening)
	{
		case '(':	closing = ')'; break;
		case '{':	closing = '}'; break;
		case '[':	closing = ']'; break;
		befault: break;
	}
	counter--;
	if(counter < 0) 
	{
		cout << fileName << ':' << row << " - error, \"" << closing << "\" without \"" << opening << "\"" << endl;
		counter = 0;
	}
}

void analyzer_t::analyze(const string& name, deque<pair<int, string> >& tokens)
{
	declared = new vector<string>();
	fileName = name;
	declareKeywords();
	bool typeFlag = false;
	bool afterMain = false;
	if(tokens[0].second != "main" && tokens[1].second != "{")
		cout << fileName << ':' << tokens[0].first << " - error, illegal - no 'main' before" << endl;
	while(tokens.size() > 0)
	{
		pair <int, string> p = tokens[0];
		tokens.pop_front();
		if(p.second == "main" && afterMain == false)
		{
			(*declared).push_back(p.second);
			afterMain = true;
			continue;
		}
		doIfBracket(p);
		find3InARow(plusCounter, fileName, p, '+');
		find3InARow(minusCounter, fileName, p, '-');
		if(p.second == "if" || p.second == "else")
		{
			checkIfElse(p);
			continue;
		}
		if(isType(p.second) && !typeFlag)
		{
			typeFlag = true;
			continue;
		}
		checkTokenValue(typeFlag, p);
	}
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
void analyzer_t::doIfBracket(const pair<int, string>& token)
{
	switch(token.second[0])
	{
		case '(': parentheses++;
				break;
		case ')': findUnordered(parentheses, fileName, token.first, '(');
				break;
		case '{': braces++;
				break;
		case '}': findUnordered(braces, fileName, token.first, '{');
				break;
		case '[': brackets++;
				break;
		case ']': findUnordered(brackets, fileName, token.first, '[');
				break;
		default: break;			
	}
		
}
void analyzer_t::checkIfElse(const pair<int, string>& token)
{
	if(token.second == "if")
	{
		ifCounter++;
	}
	if(token.second == "else")
	{
		ifCounter--;
		if(ifCounter < 0)
		{
			cout << fileName << ':' << token.first << " - error, \"else\" without \"if\"" << endl;
			ifCounter = 0;
		}
	}
}
void analyzer_t::checkTokenValue(bool& isAfterType, const pair<int, string>& token)
{
	if(isAfterType)
	{
		isAfterType = false;			
		if(isLegalVarName(token.second, token.first))
		{
			if(isDeclared(token.second))
			{
				cout << fileName << ':' << token.first << " - error, variable '" << token.second << "' already declared" << endl;
			}
			else
			{
				(*declared).push_back(token.second);
			}
		}
	}
	else if(strchr(analyzer_t::nsDelimiters.c_str(), token.second[0]) == 0)
	{
		bool isNumeric = true;
		for(int i = 0; i < token.second.length(); i++)
		{
			if(!isdigit(token.second[i])) isNumeric = false;
		}
		if(!isNumeric && !isDeclared(token.second) && !isKeyword(token.second))
		{
			cout << fileName << ':' << token.first << " - error, '" << token.second << "' is not declared" << endl;
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
	parentheses = 0; braces = 0; brackets = 0; plusCounter = 0; minusCounter = 0; ifCounter = 0; (*declared).clear();
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
bool analyzer_t::isLegalVarName(const string& token, int line)
{
	if(!isalpha(token[0]) || isKeyword(token))
	{
		cout << fileName << ':' << line << " - error, illegal variable name" << endl;
		return false;
	}
	for(int i = 1; i < token.length(); i++)
	{
		if(!isalnum(token[i]))
		{
			cout << fileName << ':' << line << " - error, illegal variable name" << endl;
			return false;
		}
	}
	if(isType(token))
	{
		cout << fileName << ':' << line << " - error, multiple type declaration" << endl;
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