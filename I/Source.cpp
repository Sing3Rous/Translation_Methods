#include "DynamicTable.h"
#include "StaticTable.h"

int main() {
	int a;
	/*StaticTable keyWords("key words.txt");
	cout << keyWords.find("int") << endl;
	cout << keyWords.find("float") << endl;
	cout << keyWords.find("while") << endl;
	cout << keyWords.find("for") << endl;
	cout << keyWords.find("return") << endl;*/

	/*StaticTable operations("operations.txt");
	cout << operations.find("+") << endl;
	cout << operations.find("-") << endl;
	cout << operations.find("<=") << endl;
	cout << operations.find(">=") << endl;
	cout << operations.find("==") << endl;
	cout << operations.find("<") << endl;
	cout << operations.find(">") << endl;
	cout << operations.find("*") << endl;*/

	/*StaticTable delimiters;
	delimiters.init({ "{", "}", "(", ")", "\t", "\n", ";", ",", " " });
	cout << delimiters.find("\n") << endl;
	cout << delimiters.find("}") << endl;
	cout << delimiters.find(";") << endl;
	cout << delimiters.find("{") << endl;
	cout << delimiters.find("\t") << endl;
	cout << delimiters.find("(") << endl;
	cout << delimiters.find(",") << endl;
	cout << delimiters.find(" ") << endl;
	cout << delimiters.find("/*") << endl;
	cout << delimiters.find("//") << endl;
	cout << delimiters.find(")") << endl;*/


	/*DynamicTable identificators;
	identificators.add("africa");
	identificators.add("alice");
	identificators.add("Africa");
	identificators.add("_rose");
	identificators.add("_grose");
	identificators.add("Santa_");
	identificators.add("mask");
	cout << identificators.find("africa").first << "\t" << identificators.find("africa").second << endl;
	cout << identificators.find("alice").first << "\t" << identificators.find("alice").second << endl;
	cout << identificators.find("Africa").first << "\t" << identificators.find("Africa").second << endl;
	cout << identificators.find("_rose").first << "\t" << identificators.find("_rose").second << endl;
	cout << identificators.find("_grose").first << "\t" << identificators.find("_grose").second << endl;
	cout << identificators.find("Santa_").first << "\t" << identificators.find("Santa_").second << endl;
	cout << identificators.find("mask").first << "\t" << identificators.find("mask").second << endl;*/

	DynamicTable constants;
	constants.add("a");
	constants.add("d");
	constants.add("A");
	constants.add("D");
	constants.add("a1");
	constants.add("d1");
	constants.add("300");
	constants.add("3");
	constants.add("10");
	constants.add("-10");
	constants.add("-3");
	constants.add("999");
	cout << constants.find("a").first << "\t" << constants.find("a").second << endl;
	cout << constants.find("d").first << "\t" << constants.find("d").second << endl;
	cout << constants.find("A").first << "\t" << constants.find("A").second << endl;
	cout << constants.find("D").first << "\t" << constants.find("D").second << endl;
	cout << constants.find("a1").first << "\t" << constants.find("a1").second << endl;
	cout << constants.find("d1").first << "\t" << constants.find("d1").second << endl;
	cout << constants.find("300").first << "\t" << constants.find("300").second << endl;
	cout << constants.find("3").first << "\t" << constants.find("3").second << endl;
	cout << constants.find("10").first << "\t" << constants.find("10").second << endl;
	cout << constants.find("-10").first << "\t" << constants.find("-10").second << endl;
	cout << constants.find("-3").first << "\t" << constants.find("-3").second << endl;
	cout << constants.find("999").first << "\t" << constants.find("999").second << endl;
	cout << constants.getValue({ 26, 1 }) << endl;

	cin >> a;
	return 0;
}