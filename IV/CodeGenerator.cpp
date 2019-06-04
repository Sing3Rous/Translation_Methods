#include "CodeGenerator.h"

void CodeGenerator::generate(ofstream &file, DynamicTable identifiers) {

	file << ".386\n.MODEL FLAT, STDCALL\n\n";
	file << "EXTRN\tExitProcess@4:NEAR\n";

	string type;

	file << "\n\n\n.data\n";
	file << "\ttmp_var_eq\tdd\t?" << endl;

	for (auto arrays : identifiers.data) {

		for (auto identifier : arrays) {

			if (identifier.name != "") {

				file << "\t" + identifier.name + "\t" + "dd" + " ?" << endl;
			}
		}
	}

	file << "\n\n.code\n";
	file << "\tSTART:" << endl;
	file << "\n\tfinit\n\n" << endl;

	stack <string> asm_stack;
	for (int i = 0; i < postfixEntry.size(); ++i) {

		auto token = postfixEntry[i];
		
		//assignment
		if (token.lexem == "=") {

			asm_stack.pop();
			file << "\tfistp " + asm_stack.top() + "\n\n";
			asm_stack.pop();
		}
		if (token.lexem == "+=") {

			asm_stack.pop();
			file << "\tfild " + asm_stack.top() + "\n";
			file << "\tfadd\n";
			file << "\tfistp " + asm_stack.top() + "\n\n";
			asm_stack.pop();
		}
		if (token.lexem == "-=") {

			asm_stack.pop();
			file << "\tfild " + asm_stack.top() + "\n";
			file << "\tfsubr\n";
			file << "\tfistp " + asm_stack.top() + "\n\n";
			asm_stack.pop();
		}
		if (token.lexem == "*=") {

			asm_stack.pop();
			file << "\tfild " + asm_stack.top() + "\n";
			file << "\tfmul\n";
			file << "\tfistp " + asm_stack.top() + "\n\n";
			asm_stack.pop();
		}

		//arithmetic operations
		if (token.lexem == "+") {

			file << "\tfiadd\n\n";
			asm_stack.pop();
		}
		if (token.lexem == "-") {

			file << "\tfisubr\n\n";
			asm_stack.pop();
		}

		//comparison operations
		if (token.lexem == "<") {

			file << "\tfstp edx\n";
			file << "\tfstp ecx\n";
			file << "\tlt edx ecx\n";
			file << "\tfild edx\n\n";
			asm_stack.pop();
		}
		if (token.lexem == ">") {

			file << "\tfstp edx\n";
			file << "\tfstp ecx\n";
			file << "\tgt edx ecx\n";
			file << "\tfild edx\n\n";
			asm_stack.pop();
		}
		if (token.lexem == "<=") {

			file << "\tfstp edx\n";
			file << "\tfstp ecx\n";
			file << "\tle edx ecx\n";
			file << "\tfild edx\n\n";
			asm_stack.pop();
		}
		if (token.lexem == ">=") {

			file << "\tfstp edx\n";
			file << "\tfstp ecx\n";
			file << "\tge edx ecx\n";
			file << "\tfild edx\n\n";
			asm_stack.pop();
		}

		//labels
		if (token.tableName == "label") {

			if (i + 1 != postfixEntry.size() && (postfixEntry[i + 1].lexem == ":" || postfixEntry[i + 1].lexem == "?")) {

				if (postfixEntry[i + 1].lexem == ":") {

					file << "\tftst\n";
					file << "\tfstp tmp_var_eq\n";
					file << "\tfstsw ax\n\tsahf\n";
					file << "\tje label" + to_string(postfixEntry[i + 1].firstPos) + "\n\n";
				}
				if (postfixEntry[i + 1].lexem == "?") {

					file << "\tjmp label" + to_string(postfixEntry[i + 1].firstPos) + "\n\n";
				}
			} else {

				file << "\tlabel" + token.lexem << ":\n\n";
			}
		}

		//variables and constants
		if (token.tableName == "Identifiers") {

			file << "\tfild " + token.lexem + "\n";
			asm_stack.push(token.lexem);
		}
		if (token.tableName == "Constants") {

			file << "\tmov tmp_var, " + token.lexem + "\n";
			file << "\tfild tmp_var\n";
			asm_stack.push(token.lexem);
		}
	}
	file << "\tCALL ExitProcess@4\n";
	file << "END START\n";
}
