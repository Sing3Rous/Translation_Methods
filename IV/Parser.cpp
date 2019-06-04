#include "Parser.h"

void Parser::fillParseTable(ifstream &file) {

	int linesCount;
	file >> linesCount;
	parseTable.resize(linesCount);
	
	int terminalsCount;

	for (int i = 0; i < linesCount; ++i) {

		file >> terminalsCount;
		for (int j = 0; j < terminalsCount; ++j) {

			string terminal;
			file >> terminal;
			parseTable[i].terminals.insert(terminal);
		}

		file >> parseTable[i].jmp;
		file >> parseTable[i].accpt;
		file >> parseTable[i].stck;
		file >> parseTable[i].rtrn;
		file >> parseTable[i].err;
	}
}

void Parser::callError(string errorMessage) {

	errorsFile << "Error: Syntax Error: " + errorMessage;
}

int Parser::getPriority(string tokenName) {
	
	if (tokenName == "+" || tokenName == "-") {

		return -10;
	}
	if (tokenName == ">" || tokenName == "<" || tokenName == ">=" || tokenName == "<=") {

		return -11;
	}
	if (tokenName == "=" || tokenName == "+=" || tokenName == "-=" || tokenName == "*=") {

		return -15;
	}
}

void Parser::parse(StaticTable &keyWords, StaticTable &delimiters, StaticTable &operations, DynamicTable &constants, DynamicTable &identifiers) {

	bool isNoErrors = true;
	bool isPostfix = false;
	bool isPostfixInStack = false;
	vector <vector <Token>> postfixStack;
	int currentPos = 1;
	int labelNum = 1;
	int numOfWhiles = 0;
	vector <pair <int, int>> labelStack;
	vector <int> stack;
	int i = 0;
	int currentType = -1; //none
	vector <Token> termList;

	while (i < tokens.size() && isNoErrors) {

		ParseTableItem currentItem = parseTable[currentPos - 1];
		string name = tokens[i].lexem;
		if (tokens[i].tableName == "Constants") {

			name = "const";
		}
		if (tokens[i].tableName == "Identifiers") {

			name = "var";
		}

		if (!currentItem.terminals.count(name)) {

			if (currentItem.err) {

				callError("Unexpected terminal: " + tokens[i].lexem);
				isNoErrors = false;
				continue;
			}
			currentPos++;
		} else {

			//for var
			if (currentPos == 53 && tokens[i + 1].lexem == "=" || currentPos == 15 || currentPos == 42) {

				isPostfix = true;
			}

			if ((name == ";" || name == "," || currentPos == 43) && isPostfix) {

				isPostfix = false;

				if (!isPostfixInStack) {

					makePostfix(termList, postfixEntry, delimiters);
				} else {

					postfixStack.push_back(vector <Token>());
					makePostfix(termList, postfixStack[postfixStack.size() - 1], delimiters);
				}
				termList.clear();
			}

			if (currentItem.accpt) {

				if (isPostfix) {

					termList.push_back(tokens[i]);
				}
				if (currentPos == 1 || currentPos == 50) {

					currentType = 1;
				}
				if (currentPos == 77) {

					identifiers.setInit(make_pair(tokens[i - 1].firstPos, tokens[i - 1].secondPos), true);
				}
				if (currentPos == 41) {

					postfixEntry.push_back(makeLabel(labelNum));
					labelNum++;
					//Token nextLine;
					//nextLine.firstPos = delimiters.find("\n");
					//nextLine.tableName = "Delimiters";
					//nextLine.lexem = "\n";
					//nextLine.secondPos = -1;
					//postfixEntry.push_back(nextLine);
				}
				if (currentPos == 43) {

					labelStack.push_back(make_pair(labelNum - 1, labelNum));
					postfixEntry.push_back(makeLabel(labelNum));
					labelNum++;
					//very bad code start:
					Token colon;
					colon.lexem = ":";
					//colon.tableName = "label";
					colon.firstPos = labelNum - 2;
					postfixEntry.push_back(colon);
					//very bad code end.
					Token nextLine;
					nextLine.firstPos = delimiters.find("\n");
					nextLine.tableName = "Delimiters";
					nextLine.lexem = "\n";
					nextLine.secondPos = -1;
					postfixEntry.push_back(nextLine);
				}
				if (currentPos == 46) {

					postfixEntry.push_back(makeLabel(labelStack[numOfWhiles].first));
					//postfixEntry.push_back(makeLabel(labelNum - 2));
					//very bad code start:
					Token questionMark;
					questionMark.lexem = "?";
					//questionMark.tableName = "label";
					reverse(begin(labelStack), end(labelStack));
					questionMark.firstPos = labelStack[numOfWhiles].second;
					postfixEntry.push_back(questionMark);
					Token nextLine;
					nextLine.firstPos = delimiters.find("\n");
					nextLine.tableName = "Delimiters";
					nextLine.lexem = "\n";
					nextLine.secondPos = -1;
					postfixEntry.push_back(nextLine);
					//very bad code end.
					postfixEntry.push_back(makeLabel(labelStack[numOfWhiles].second));
					numOfWhiles++;
					//postfixEntry.push_back(makeLabel(labelNum - 1));

				}
				if (name == "var") {
				
					//if needs an assignment
					if (currentPos == 15 || currentPos == 37) {

						if (identifiers.getType(make_pair(tokens[i].firstPos, tokens[i].secondPos)) == -1) {

							callError("Undefined identifier: " + tokens[i].lexem);
							isNoErrors = false;
							continue;
						}
						if (currentPos == 39) {

							identifiers.setInit(make_pair(tokens[i].firstPos, tokens[i].secondPos), true);
						}
					}

					//if it is an assignment
					if (currentPos == 53) {

						if (identifiers.getType(make_pair(tokens[i].firstPos, tokens[i].secondPos)) != -1) {

							callError("Reinitializating: " + tokens[i].lexem);
							isNoErrors = false;
							continue;
						}
						identifiers.setType(make_pair(tokens[i].firstPos, tokens[i].secondPos), currentType);
					}
				}
				i++;
			}
			if (currentItem.stck) {

				stack.push_back(currentPos + 1);
			}
			if (currentItem.rtrn) {

				if (currentPos == 7) {

					continue;
				}
				currentPos = stack[stack.size() - 1];
				if (stack.size() == 0) {

					cout << "Table error";
					isNoErrors = false;
					continue;
				}
				stack.pop_back();
			}
			if (!currentItem.rtrn) {

				currentPos = currentItem.jmp;
			}
		}
	}
}

void Parser::makePostfix(vector<Token> termList, vector<Token> &postfixList, StaticTable delimiters) {

	stack <Token> postfixStack;

	for (auto token : termList) {

		string name = token.lexem;
		if (token.tableName == "Identifiers" || token.tableName == "Constants") {

			postfixList.push_back(token);
			continue;
		}
		if (name == "(") {

			postfixStack.push(token);
		}
		if (name == ")") {

			auto topToken = postfixStack.top();
			while (topToken.lexem != "(") {

				postfixList.push_back(topToken);
				topToken = postfixStack.top();
				postfixStack.pop();
			}
			continue;
		}

		while (!postfixStack.empty() && getPriority(postfixStack.top().lexem) >= getPriority(name)) {

			postfixList.push_back(postfixStack.top());
			postfixStack.pop();
		}
		postfixStack.push(token);
	}
	while (!postfixStack.empty()) {

		postfixList.push_back(postfixStack.top());
		postfixStack.pop();
	}
	Token nextLine;
	nextLine.firstPos = delimiters.find("\n");
	nextLine.tableName = "Delimiters";
	nextLine.lexem = "\n";
	nextLine.secondPos = -1;
	postfixEntry.push_back(nextLine);
}

void Parser::writePostfix(ofstream &file) {

	for (auto lexem : postfixEntry) {

		file << lexem.lexem;
		if (lexem.lexem != "\n") {

			file << " ";
		}
	}
}

Token Parser::makeLabel(int num) {

	Token label;
	label.lexem = to_string(num);
	label.tableName = "label";
	return label;
}
