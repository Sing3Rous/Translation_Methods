#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

const int NUM_OF_LETTERS_ENG = 26;

// [0, 26)  - lexems with first symbol ['A', 'Z']
// [26, 52) - lexems with first symbol ['a', 'z']
// [52, 53) - lexems with first symbol '_'
// [53, 54) - lexems with first symbol ['0', '9']
// [54, 55) - lexems with first symbol '-'

struct Attributes {

	Attributes(const string &_name, int _value, int _type) : name(_name), value(_value), type(_type) {};
	string name;
	int value;
	int type;
	bool isInitialized = false;
};

class DynamicTable {

public:
	DynamicTable() = default;
	~DynamicTable() = default;

	void add(const string &unit);
	pair <int, int> find(const string &unit) const;
	int getValue(pair <int, int> token) const;
	void setValue(pair <int, int> token, int value);
	int getType(pair <int, int> token) const;
	void setType(pair <int, int> token, int value);
	void setInit(pair <int, int> token, bool init);

private:
	vector <Attributes> data[NUM_OF_LETTERS_ENG * 2 + 3];

};