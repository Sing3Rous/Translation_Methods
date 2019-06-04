#include "CodeGenerator.h"

void CodeGenerator::generate(ofstream &file, DynamicTable identifiers, DynamicTable constants) {

	file << ".386" << endl <<
		".MODEL FLAT, STDCALL" << endl <<
		"EXTERN  ExitProcess@4: PROC\n" <<
		".DATA" << endl;

	for (auto arrays : identifiers.data) {

		for (auto identifier : arrays) {

			if (identifier.name != "") {

				file << identifier.name + " " + "dd " + "?" << endl;
			}
		}
	}
	file << ".CODE" << endl << "MAIN PROC" << endl;
	bool findResultToken = false;
	Token resultToken;
	int currentLabel = 0;

	for (int i = 0; i < postfixEntry.size(); i++) {
		auto token = postfixEntry[i];
		if (token.lexem == "\n") {

			findResultToken = false;
			continue;
		}
		if (token.tableName == "Operations") {

			auto operation = token.lexem;
			if (operation == "=") {

				int type;
				string name;
				if (resultToken.tableName != "label" && token.lexem != ":" && token.lexem != "?") {

					type = identifiers.getType(make_pair(resultToken.firstPos, resultToken.secondPos));
					name = identifiers.getName(make_pair(resultToken.firstPos, resultToken.secondPos));
				} else {

					type = -1;
					name = resultToken.lexem;
				}
				file << "pop " + resultToken.lexem + "\n";
				findResultToken = false;
				file << "pop eax\n";
			} else {

				file << "pop eax\n";
				file << "pop ebx\n";
				if (operation == "+") {

					file << "add ebx, eax\n";
					file << "push ebx\n";
				}
				if (operation == "-") {

					file << "sub ebx, eax\n";
					file << "push ebx\n";
				}
				if (operation == ">" || operation == "<") {

					string successLabel = "CMPSuccess" + to_string(currentLabel);
					string resultLabel = "CMPResult" + to_string(currentLabel);
					file << "cmp ebx, eax\n";
					if (operation == ">") {

						file << "jg " + successLabel + "\n";
					} else {

						file << "jl " + successLabel + "\n";
					}
					file << "push 0\n";
					file << "mov ecx, 0\n";
					file << "jmp " + resultLabel + "\n";
					file << successLabel + ":\n";
					file << "push 1\n";
					file << "mov ecx, 1\n";
					file << resultLabel + ":\n";
					currentLabel++;
				}
				if (operation == ">=" || operation == "<=") {

					string successLabel = string("CMPSuccess") + to_string(currentLabel);
					string resultLabel = string("CMPResult") + to_string(currentLabel);
					file << "cmp ebx, eax\n";
					if (operation == ">=") {

						file << "jge " + successLabel + "\n";
					} else {

						file << "jle " + successLabel + "\n";
					}
					file << "push 0\n";
					file << "mov ecx, 0\n";
					file << "jmp " + resultLabel + "\n";
					file << successLabel + ":\n";
					file << "push 1\n";
					file << "mov ecx, 1\n";
					file << resultLabel + ":\n";
					currentLabel++;
				}
			}
		} else {

			if (token.tableName == "Identifiers") {

				file << "push " + token.lexem + "\n";
				if (findResultToken == false) {

					resultToken = token;
					findResultToken = true;
				}
			} else {

				if (token.tableName != "label" && token.lexem != ":" && token.lexem != "?") {

					file << "push " + constants.getName(make_pair(token.firstPos, token.secondPos)) + "\n";
				}
			}
		}
		if (token.tableName == "label") {

			if (i + 1 != postfixEntry.size() && (postfixEntry[i + 1].lexem == ":" || postfixEntry[i + 1].lexem == "?")) {

				if (postfixEntry[i + 1].lexem == ":") {

					file << "cmp ecx, 0\n";
					file << "je label" + token.lexem + "\n";
				}
				if (postfixEntry[i + 1].lexem == "?") {

					file << "jmp label" + token.lexem + "\n";
				}
			} else {

					file << "label" + token.lexem << ":\n";
			}
		}
	}
	file << "PUSH 0\n" <<
		"CALL ExitProcess@4\n" <<
		"MAIN ENDP\nEND MAIN\n";
}