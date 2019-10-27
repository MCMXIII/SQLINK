#include <fstream>
#include <ctype.h>
#include <iostream>
#include <string>
#include <string.h>
#include <deque>
#include <vector>
#include "analyzer_t.h"

const string types[7] = {"char", "short", "int", "long", "float", "double", "void"};
const string keywords[11] = {"if", "else", "for", "while", "class", "private", "public", "protected", "main", "const", "virtual"};

using namespace std;
		
void find3InARow(int& counter, const string& fileName, const pair<int, string>& token, const char& c)
{
	if(token.second[0] == c)
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

		
void findUnordered(int& counter, const string& fileName, const int& row, const char& c, const char& c2)
{
	counter--;
	if(counter < 0) 
	{
		cout << fileName << ':' << row << " - error, \"" << c << "\" without \"" << c2 << "\"" << endl;
		counter = 0;
	}
}

void analyzer_t::analyze(const string& fileName, deque<pair<int, string> >& tokens)
{
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
			declared.push_back(p.second);
			afterMain = true;
			continue;
		}
		switch(p.second[0])
		{
			case '(': parentheses++;
					break;
			case ')': findUnordered(parentheses, fileName, p.first, ')', '(');
					break;
			case '{': braces++;
					break;
			case '}': findUnordered(braces, fileName, p.first, '}', '{');
					break;
			case '[': brackets++;
					break;
			case ']': findUnordered(brackets, fileName, p.first, ']', '[');
					break;
			default: break;			
		}
		
		find3InARow(plusCounter, fileName, p, '+');
		find3InARow(minusCounter, fileName, p, '-');
		if(p.second == "if")
		{
			ifCounter++;
			continue;
		}
		if(p.second == "else")
		{
			ifCounter--;
			if(ifCounter < 0)
			{
				cout << fileName << ':' << p.first << " - error, \"else\" without \"if\"" << endl;
				ifCounter = 0;
			}
			continue;
		}
		if(isType(p.second) && !typeFlag)
		{
			typeFlag = true;
			continue;
		}
		if(typeFlag)
		{
			typeFlag = false;			
			if(isLegalVarName(p.second, fileName, p.first))
			{
				if(isDeclared(p.second))
				{
					cout << fileName << ':' << p.first << " - error, variable '" << p.second << "' already declared" << endl;
				}
				else
				{
					declared.push_back(p.second);
				}
			}
		}
		else if(strchr("()[]{};<>=+-*&", p.second[0]) == 0)
		{
			bool isNumeric = true;
			for(int i = 0; i < p.second.length(); i++)
			{
				if(!isdigit(p.second[i])) isNumeric = false;
			}
			if(!isNumeric && !isDeclared(p.second))
			{
				cout << fileName << ':' << p.first << " - error, '" << p.second << "' is not declared" << endl;
			}
		}
	}
	if(parentheses > 0) cout << fileName << " - error, " << parentheses << " '(' not closed" << endl;
	if(brackets > 0) cout << fileName << " - error, " << brackets << " '[' not closed" << endl;
	if(braces > 0) cout << fileName << " - error, " << braces << " '{' not closed" << endl;
	parentheses = 0; braces = 0; brackets = 0; plusCounter = 0; minusCounter = 0; ifCounter = 0; declared.clear();
}
bool analyzer_t::isType(const string& token)
{
	for(int i = 0; i < 7; i++)
	{
		if(token == types[i])
			return true;
	}
	return false;
}
bool analyzer_t::isKeyword(const string& token)
{
	for(int i = 0; i < 11; i++)
	{
		if(token == keywords[i])
			return true;
	}
	return false;

}
bool analyzer_t::isLegalVarName(const string& token, const string& fileName, int line)
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
	vector<string>::iterator it = declared.begin();
	while(it != declared.end())
	{
		if(token == *it++)
			return true;
	}
	return false;
}