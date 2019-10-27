#include <fstream>
#include <string>
#include <deque>
#include <utility>
#include <iostream>
#include "tokenizer_t.h"
#include "analyzer_t.h"
#include "parser_t.h"

void parser_t::parse(const string& name)
{
	openFile(name);
	if(fileName == "*")
	{
		cout << "error - cannot open file " << name << endl;
	}
	char line[513];
	while(stream.getline(line, 513))
	{
		string lineStr(line);
		(*tokenizer).tokenize(lineStr, lineNumber, tokens);
		lineNumber++;
	}
	(*analyzer).analyze(name, tokens);
	closeFile();
}