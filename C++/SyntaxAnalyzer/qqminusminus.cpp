#include "parser_t.h"
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
	parser_t parser;
	for(int i = 1; i < argc; i++)
	{
		string arg(argv[i]);
		parser.parse(arg);
	}
}