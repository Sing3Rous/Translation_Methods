#include "StaticTable.h"

void StaticTable::upload(const string &fileName) {

	ifstream in(fileName);
	string unit;
	while (in >> unit) {
		data.push_back(unit);

	}
	in.close();
}

void StaticTable::init(const vector <string> &_data) {

	data = _data;
}

int StaticTable::find(const string &unit) const {

	for (int i = 0; i < data.size(); ++i) {
		if (unit == data[i]) return i;

	}
	return -1;
}

StaticTable::StaticTable(const string &fileName) {

	upload(fileName);
}