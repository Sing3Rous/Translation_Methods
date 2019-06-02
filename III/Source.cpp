#include "Parser.h"

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
	//const string text = "int main() {\nint a = 0;\nint b = 5 + a;\n}";
	//const string text = "int main() {\nint a = 0;\nint b = 5 + a;\n}";
	//const string text = "int main (){\nint ba = 53453;\nint ab = ba + 3231;\nda = 23;\nda = ba + ab;}";
	//const string text = "int main (){\nint ba = 53453;\nint ab = ba + 3231, da = 23;\nda = ba + ab;\nint i, j=2;\n}";
	//const string text = "int main (){\nint ba = 53453;\nint ab = ba + 3231, da = 23;\nda = ba + ab;\nint i, j=2; while(i < 5) { j = j+2; };\n}";
	//const string text = "int main(){\nint a = 1;\nwhile(a<5){a = a + 1;}}";
	//const string text = "int main(){\nint a = 1;\nwhile(a<5){while(a<6){a = a + 1;}}}";
	const string text = "int main(){int ba = 53453;int ab = ba + 3231, da = 23; da = ba + ab; int i = 0; int j; while(i < 1){ba = ba + 1; i = i + 1;}}";
	//const string text = "int main(){\nint a, b = 0;}";

	//const string text = "/int a=5;int b=23; while/*(a<b)*/{a=a+5};return a;";
	//const string text = "while(a<b)\n{\na=a+5;\n};\nreturn @0+a#;";
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
	tokens = dfa.tokenize(keyWords, delimiters, operations, constants, identifiers);
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

	ofstream postfixFile("postfix_file.txt");
	ifstream parseTableFile("parse_table_file.txt");
	Parser parser(tokens);
	parser.fillParseTable(parseTableFile);
	parser.parse(keyWords, delimiters, operations, constants, identifiers);
	parser.writePostfix(postfixFile);

	out << "-----------------------------------------------------------------";
	out.close();
	return 0;
}