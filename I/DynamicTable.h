#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

const int NUM_OF_LETTERS_ENG = 26;

struct Attributes {
	Attributes(const string &_name, int _value) : name(_name), value(_value) {};
	string name;
	int value;

};

class DynamicTable {
public:
	DynamicTable() = default;
	~DynamicTable() = default;

	void add(const string &unit);
	pair <int, int> find(const string &unit) const;
	int getValue(pair <int, int> token) const;
	void setValue(pair <int, int> token, int value);

private:
	vector <Attributes> data[NUM_OF_LETTERS_ENG * 2 + 3];

};