#include <fstream>
#include <string>
#include <deque>
#include <sstream>
#include <utility>
#include <ctype.h>
#include "tokenizer_t.h"

string tokenizer_t::delimiters = " \t\n\v\f\r()[]{};<>=+-*&";

int calculateSizeToRead(const string& line, const int& i, const string& del)
{
	int firstOf = line.find_first_of(del, i);
	if(firstOf < 0)
	{
		return line.length() - i;
	}
	else
	{
		return firstOf - i;
	}
}

void tokenizer_t::tokenize(const string& line, const int& lineNum, deque<pair<int, string> >& tokens)
{
	stringstream sstream(line);
	int i = 0;
	char space[1];
	while(i < line.length())
	{
		int sizeToRead = calculateSizeToRead(line, i, delimiters);
		while(sizeToRead == 0)
		{
			if(!isspace(line[i]))
				sizeToRead = 1;
			else
			{
				sstream.read(space, 1);
				i++;
				sizeToRead = calculateSizeToRead(line, i, delimiters);
			}
			if(i >= line.length())
			{
				return;
			}
		}
		char* token = new char[sizeToRead + 1];
		token[sizeToRead] = 0;
		sstream.read(token, sizeToRead);
		if(!isspace(token[0]) && sizeToRead > 0)
		{
			string tokenStr(token);
			pair<int, string> p;
			p.first = lineNum;
			p.second = tokenStr;
			tokens.push_back(p);
		}
		i+=sizeToRead;
		delete [] token;
	}
}