#include <fstream>
#include <string>
#include <deque>
#include <iostream>
#include "tokenizer_t.h"
#include "analyzer_t.h"
#include "parser_t.h"

parser_t::parser_t() { tokenizer = new tokenizer_t(); analyzer = new analyzer_t(); }
parser_t::~parser_t() { closeFile(); delete tokenizer; delete analyzer; }
void parser_t::parse(const string& name)
{
	openFile(name);
	if(fileName == "*")
	{
		cout << "error - cannot open file " << name << endl << endl;
		return;
	}
	char line[513];
	(*analyzer).init(name);
	while(stream.getline(line, 513))
	{
		if(!stream.good())
		{
			cout << "error - cannot read from file " << name << endl << endl;
			break;
		}
		string lineStr(line);
		(*tokenizer).tokenize(lineStr, tokens);
		(*analyzer).analyze(tokens);
	}
	(*analyzer).finish();
	closeFile();
	cout << endl;
}