#include "Tokenizer.h"

DFA::DFA(const string &text) : text(text), pos(0), state(START) { this->initializeStateTable(); };

bool DFA::isFinalState(void) const {

	return
		state == ADD ||
		state == PUSH ||
		state == ERROR ||
		state == SKIP;
}

string DFA::getLexem(void) const {

	string lex = lexem;

	if (state == PUSH) {

		lex.pop_back();
	}

	return lex;
}

Symbol DFA::getSymbolType(char symbol) {

	if (symbol >= 'a' && symbol <= 'z' || symbol >= 'A' && symbol <= 'Z' || symbol == '_') {

		return LETTER;
	}
	if (symbol >= '0' && symbol <= '9') {

		return NUMERAL;
	}
	if (symbol == ',' || symbol == ';' || symbol == '{' || symbol == '}' ||
		symbol == '(' || symbol == ')') {

		return DELIMETER;
	}
	if (symbol == '+' || symbol == '-') {

		return ARITHMETIC_OPERATION;
	}
	if (symbol == '<') {

		return LESS_SYMBOL;
	}
	if (symbol == '>') {

		return MORE_SYMBOL;
	}
	if (symbol == '=') {

		return EQUAL_SYMBOL;
	}
	if (symbol == '*') {

		return ASTERISK_SYMBOL;
	}
	if (symbol == '/') {

		return SLASH_SYMBOL;
	}
	return OTHER;
}

bool DFA::automating(void) {

	if (state == PUSH) {

		pos--;
	}
	if (isFinalState()) {

		state = START;
		lexem = "";
	}
	char symbol = text[pos];
	state = nextState(getSymbolType(symbol), state);
	lexem += symbol;

	if (state == ERROR && lexem[0] == '/') pos--;

	pos++;

	return pos <= text.size();
}

bool DFA::initializeStateTable(void) {

	stateTable.resize(9);

	int i = 0;

	//Start
	stateTable[i].push_back(NAME);
	stateTable[i].push_back(NUMBER);
	stateTable[i].push_back(ADD);
	stateTable[i].push_back(ADD);
	stateTable[i].push_back(MORE);
	stateTable[i].push_back(LESS);
	stateTable[i].push_back(COMMENTARY);
	stateTable[i].push_back(ERROR);
	stateTable[i].push_back(ADD);
	stateTable[i].push_back(ERROR);
	stateTable[i++].push_back(ADD);
	
	//NAME
	stateTable[i].push_back(NAME);
	stateTable[i].push_back(NAME);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i++].push_back(PUSH);

	//NUMBER
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(NUMBER);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i++].push_back(PUSH);

	//MORE
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(ADD);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i++].push_back(PUSH);

	//LESS
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(ADD);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i].push_back(PUSH);
	stateTable[i++].push_back(PUSH);

	//COMMENTARY
	stateTable[i].push_back(ERROR);
	stateTable[i].push_back(ERROR);
	stateTable[i].push_back(ERROR);
	stateTable[i].push_back(ERROR);
	stateTable[i].push_back(ERROR);
	stateTable[i].push_back(ERROR);
	stateTable[i].push_back(SINGLE_LINE_COMMENTARY);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(ERROR);
	stateTable[i].push_back(ERROR);
	stateTable[i++].push_back(ERROR);

	//SINGLE COMMENTARY
	stateTable[i].push_back(SINGLE_LINE_COMMENTARY);
	stateTable[i].push_back(SINGLE_LINE_COMMENTARY);
	stateTable[i].push_back(SINGLE_LINE_COMMENTARY);
	stateTable[i].push_back(SINGLE_LINE_COMMENTARY);
	stateTable[i].push_back(SINGLE_LINE_COMMENTARY);
	stateTable[i].push_back(SINGLE_LINE_COMMENTARY);
	stateTable[i].push_back(SINGLE_LINE_COMMENTARY);
	stateTable[i].push_back(SINGLE_LINE_COMMENTARY);
	stateTable[i].push_back(SKIP);
	stateTable[i].push_back(SINGLE_LINE_COMMENTARY);
	stateTable[i++].push_back(SINGLE_LINE_COMMENTARY);

	//MULTIPLE COMMENTARY
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY_END);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i++].push_back(MULTIPLE_LINES_COMMENTARY);

	//MULTIPLE COMMENTARY END
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(SKIP);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY_END);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i].push_back(MULTIPLE_LINES_COMMENTARY);
	stateTable[i++].push_back(MULTIPLE_LINES_COMMENTARY);

	return true;
}

State DFA::nextState(Symbol symbol, State state) {

	return stateTable[state][symbol];
}

WhichTableToAdd DFA::getTableType(void) {

	auto symbol = getSymbolType(lexem[0]);

	if (state == ADD || state == PUSH || state == LESS || state == MORE || state == NAME || state == NUMBER) {

		if (symbol == LETTER) return KEYWORDS_OR_IDENTIFIERS;
		if (symbol == DELIMETER) return DELIMETERS;
		if (symbol == NUMERAL) return CONSTANTS;
		if (symbol == ARITHMETIC_OPERATION || symbol == LESS_SYMBOL || symbol == MORE_SYMBOL ||
			symbol == EQUAL_SYMBOL) return OPERATIONS;
	}
	if (state == SKIP) {

		return IGNORE;
	}
	if (state == ERROR) {

		return ERR;
	}
}

int DFA::getPos(void) const {

	return pos;
}

vector <Token> DFA::tokenize(StaticTable &keyWords, StaticTable &delimiters,
	StaticTable &operations, DynamicTable &constants, DynamicTable &identifiers) {

	vector <Token> tokens;
	Token token;

	ofstream out("tokenizer_error_log.txt");

	while (this->automating()) {

		if (this->isFinalState()) {

			auto lex = this->getLexem();

			switch (this->getTableType()) {

			case KEYWORDS_OR_IDENTIFIERS:

				if (keyWords.find(lex) == -1) {

					identifiers.add(lex);
					token.tableName = "Identifiers";
					token.firstPos = identifiers.find(lex).first;
					token.secondPos = identifiers.find(lex).second;
					token.lexem = lex;
					tokens.push_back(token);
				} else {

					token.tableName = "Key Words";
					token.firstPos = keyWords.find(lex);
					token.secondPos = -1;
					token.lexem = lex;
					tokens.push_back(token);
				}
				break;
			case DELIMETERS:

				token.tableName = "Delimiters";
				token.firstPos = delimiters.find(lex);
				token.secondPos = -1;
				token.lexem = lex;
				tokens.push_back(token);
				break;
			case CONSTANTS:

				constants.add(lex);
				token.tableName = "Constants";
				token.firstPos = constants.find(lex).first;
				token.secondPos = constants.find(lex).second;
				token.lexem = lex;
				tokens.push_back(token);

				break;
			case OPERATIONS:

				token.tableName = "Operations";
				token.firstPos = operations.find(lex);
				token.secondPos = -1;
				token.lexem = lex;
				tokens.push_back(token);
				break;
			case ERR:

				out << "Error state on lexem: " << lexem << endl;
				break;
			case IGNORE:

				break;
			}
		}
	}

	/*auto lex = this->getLexem();

	switch (this->getTableType()) {

	case KEYWORDS_OR_IDENTIFIERS:

		if (keyWords.find(lex) == -1) {

			identifiers.add(lex);
			token.tableName = "Identificators";
			token.firstPos = identifiers.find(lex).first;
			token.secondPos = identifiers.find(lex).second;
			token.lexem = lex;
			tokens.push_back(token);
		}
		else {

			token.tableName = "Key Words";
			token.firstPos = keyWords.find(lex);
			token.secondPos = -1;
			token.lexem = lex;
			tokens.push_back(token);
		}
		break;
	case DELIMETERS:

		token.tableName = "Delimeters";
		token.firstPos = delimiters.find(lex);
		token.secondPos = -1;
		token.lexem = lex;
		tokens.push_back(token);
		break;
	case CONSTANTS:

		constants.add(lex);
		token.tableName = "Constants";
		token.firstPos = constants.find(lex).first;
		token.secondPos = constants.find(lex).second;
		token.lexem = lex;
		tokens.push_back(token);

		break;
	case OPERATIONS:

		token.tableName = "Operations";
		token.firstPos = operations.find(lex);
		token.secondPos = -1;
		token.lexem = lex;
		tokens.push_back(token);
		break;
	case ERR:

		out << "Error state on lexem: " << token.lexem << endl;
		break;
	case IGNORE:

		break;
	}*/

	out.close();
	return tokens;
}