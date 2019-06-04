#include "Tokenizer.h"
#include <set>
#include <stack>

struct ParseTableItem {

	set <string> terminals;
	int jmp;
	bool accpt, stck, rtrn, err;
};

class Parser
{
public:
	Parser(vector <Token> _tokens) { tokens = _tokens; errorsFile.open(("parser_error_log.txt")); }
	void fillParseTable(ifstream &parseTableFile);
	void callError(string errorMessage);
	int getPriority(string tokenName);
	void parse(StaticTable &keyWords, StaticTable &delimiters,
		StaticTable &operations, DynamicTable &constants, DynamicTable &identifiers);
	void makePostfix(vector <Token> termList, vector <Token> &postfixList, StaticTable delimiters);
	void writePostfix(ofstream &file);
	vector <Token> postfixEntry;

private:
	ofstream errorsFile;
	vector <Token> tokens;
	vector <ParseTableItem> parseTable;

	Token makeLabel(int num);
};
