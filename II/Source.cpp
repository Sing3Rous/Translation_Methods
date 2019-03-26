#include "Tokenizer.h"

//2)	Подмножество языка С++ включает:
//•	данные типа int;
//•	инструкции описания переменных;
//•	операторы присваивания, while любой вложенности и в любой последовательности;
//•	операции +, –, <=, >=, <, >.


int main() {

	/*ifstream in("test.txt");
	string text;
	string str;
	while (in >> str) {

		text += str + " ";
	};
	in.close();*/

	//const string text = "int main() {\nint a = 0;\nint b = -5;\nwhile (a < b) {\n/*\nbe\nli\nber\nda\n*\n*\n*\n*/\na = a + 1;\n}\n\nreturn 0;\n}";
	//const string text = "/int a=5;int b=23; while/*(a<b)*/{a=a+5};return a;";
	const string text = "while(a<b)\n{\na=a+5;\n};\nreturn @0+a#;";
	// const string text = "int a a0;";
	//const string text = "a - 3";
	//const string text = "@@@@  шипучка   999abv   __4a";

	ofstream out2("testi.txt");
	for (auto i : text) {

		out2 << i;
	}
	out2.close();

	StaticTable keyWords("key words.txt");
	StaticTable operations("operations.txt");
	StaticTable delimiters;
	delimiters.init({ "{", "}", "(", ")", "\t", "\n", ";", ",", " " });
	DynamicTable identifiers;
	DynamicTable constants;
	
	ofstream out("tokens.txt");
	DFA dfa(text);
	vector <Token> tokens;
	tokens = dfa.parse(keyWords, delimiters, operations, constants, identifiers);
	out << "lexem" << "\t" << "|" << "\t" << "table name" << "\t" << "|" << "\t" << "first" << 
		"\t" << "|" << "\t" << "second" << "\t" << "|" << endl;
	out << "-----------------------------------------------------------------" << endl;
	for (int i = 0; i < tokens.size(); ++i) {
		if (tokens[i].lexem == "\n") {

			out << "\\n" << "\t" << "|" << "\t" << tokens[i].tableName << "\t" << "|" << "\t"
				<< tokens[i].firstPos << "\t" << "|" << "\t" << tokens[i].secondPos << "\t" << "|" << endl;
		} else {

		out << tokens[i].lexem << "\t" << "|" << "\t" << tokens[i].tableName << "\t" << "|" <<
			"\t" << tokens[i].firstPos << "\t" << "|" << "\t" << tokens[i].secondPos << "\t" << "|" << endl;
		}
	}

	out << "-----------------------------------------------------------------";
	out.close();
	return 0;
}
