#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class StaticTable {

public:
	StaticTable() = default;
	StaticTable(const string &fileName);
	~StaticTable() = default;

	void init(const vector <string> &_data);
	void upload(const string &fileName);
	int find(const string &unit) const;

private:
	vector <string> data;
};
