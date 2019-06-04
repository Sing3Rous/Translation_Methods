#pragma once
#include "Parser.h"

class CodeGenerator
{
public:
	CodeGenerator(vector <Token> _postfixEntry) { postfixEntry = _postfixEntry; };
	void generate(ofstream &file, DynamicTable identifiers, DynamicTable constants);

private:
	vector <Token> postfixEntry;
};

