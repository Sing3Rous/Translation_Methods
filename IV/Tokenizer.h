#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "DynamicTable.h"
#include "StaticTable.h"

using namespace std;

// State Table of DFA
//--------------------------------------------------------------------------------------------------
//\\\\\\\\| LETTER | NUMERAL | + -  |  =   |  >   |  <   |  /   |   *   |  \n  | OTHER | DELIMITER |
//--------------------------------------------------------------------------------------------------
// START  |  NAME  | NUMBER  | ADD  | ADD  |  >   |  <   |  /   |  ERR  |  ADD |  ERR  |    ADD    |
//--------------------------------------------------------------------------------------------------
//  NAME  |  NAME  | NUMBER  | PUSH | PUSH | PUSH | PUSH | PUSH |  PUSH | PUSH | PUSH  |   PUSH    |
//--------------------------------------------------------------------------------------------------
// NUMBER |  PUSH  | NUMBER  | PUSH | PUSH | PUSH | PUSH | PUSH |  PUSH | PUSH | PUSH  |   PUSH    |
//--------------------------------------------------------------------------------------------------
//   >    |  PUSH  |  PUSH   | PUSH | ADD  | PUSH | PUSH | PUSH |  PUSH | PUSH | PUSH  |   PUSH    |
//--------------------------------------------------------------------------------------------------
//   <    |  PUSH  |  PUSH   | PUSH | ADD  | PUSH | PUSH | PUSH |  PUSH | PUSH | PUSH  |   PUSH    |
//--------------------------------------------------------------------------------------------------
//   /    |   ERR  |   ERR   |  ERR | ERR  | ERR  | ERR  | //.. |  /*.. |  ERR |  ERR  |    ERR    |
//--------------------------------------------------------------------------------------------------
//  //..  |  //..  |  //..   | //.. | //.. | //.. | //.. | //.. |  //.. |  IGN | //..  |   //..    |
//--------------------------------------------------------------------------------------------------
//  /*..  |  /*..  |  /*..   | /*.. | /*.. | /*.. | /*.. | /*.. | /*..* | /*.. | /*..  |   /*..    |
//--------------------------------------------------------------------------------------------------
// /*..*  |  /*..  |  /*..   | /*.. | /*.. | /*.. | /*.. |  IGN | /*..* | /*.. | /*..  |   /*..    |
//--------------------------------------------------------------------------------------------------

struct Token {

	string tableName;
	int firstPos;
	int secondPos;
	string lexem;

	bool operator ==(Token token) {

		return (tableName == token.tableName && firstPos == token.firstPos && secondPos == token.secondPos);
	}

	bool operator !=(Token token) {

		return (tableName != token.tableName || firstPos != token.firstPos || secondPos != token.secondPos);
	}

	operator bool() const {

		return !(firstPos == -1);
	}
};

enum Symbol
{
	LETTER = 0,
	NUMERAL,
	ARITHMETIC_OPERATION,
	EQUAL_SYMBOL,
	MORE_SYMBOL,
	LESS_SYMBOL,
	SLASH_SYMBOL,
	ASTERISK_SYMBOL,
	END_OF_LINE,
	OTHER,
	DELIMETER,
};

enum State
{
	START = 0,

	NAME,
	NUMBER,
	MORE,
	LESS,
	COMMENTARY,
	SINGLE_LINE_COMMENTARY,
	MULTIPLE_LINES_COMMENTARY,
	MULTIPLE_LINES_COMMENTARY_END,

	ADD,
	PUSH,
	ERROR,
	SKIP,
};

enum WhichTableToAdd
{
	KEYWORDS_OR_IDENTIFIERS,
	DELIMETERS,
	OPERATIONS,
	CONSTANTS,

	IGNORE,
	ERR,
};

// deterministic finite automaton
class DFA {

public:
	DFA(const string &text);
	bool automating(void);
	bool isFinalState(void) const;
	WhichTableToAdd getTableType(void);
	string getLexem(void) const;
	int getPos(void) const;
	State nextState(Symbol symbol, State state);
	vector <Token> tokenize(StaticTable &keyWords, StaticTable &delimiters,
		StaticTable &operations, DynamicTable &constants, DynamicTable &identifiers);

private:
	Symbol getSymbolType(char symbol);
	bool initializeStateTable(void);

	vector <vector <State>> stateTable;
	const string &text;
	State state;
	string lexem;
	int pos;
};