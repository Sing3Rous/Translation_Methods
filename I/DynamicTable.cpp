#include "DynamicTable.h"

void DynamicTable::add(const string &unit) {
	if ('a' <= unit[0] && unit[0] <= 'z') {
		data[NUM_OF_LETTERS_ENG + unit[0] - 'a'].push_back(Attributes(unit, -1));
		return;

	}
	if (unit[0] == '_') {
		data[NUM_OF_LETTERS_ENG * 2].push_back(Attributes(unit, -1));
		return;

	}
	if ('A' <= unit[0] && unit[0] <= 'Z') {
		data[unit[0] - 'A'].push_back(Attributes(unit, -1));
		return;

	}
	if ('0' <= unit[0] && unit[0] <= '9') {
		data[NUM_OF_LETTERS_ENG * 2 + 1].push_back(Attributes(unit, -1));
		return;

	}
	if (unit[0] == '-') {
		data[NUM_OF_LETTERS_ENG * 2 + 2].push_back(Attributes(unit, -1));
		return;

	}
}

pair <int, int> DynamicTable::find(const string &unit) const {
	int key, value;
	if ('a' <= unit[0] && unit[0] <= 'z') {
		for (int i = 0; i < data[NUM_OF_LETTERS_ENG + unit[0] - 'a'].size(); ++i) {
			if (unit == data[NUM_OF_LETTERS_ENG + unit[0] - 'a'][i].name) return { NUM_OF_LETTERS_ENG + unit[0] - 'a', i };

		}
		return { -1, -1 };
	} 
	if (unit[0] == '_') {
		for (int i = 0; i < data[NUM_OF_LETTERS_ENG * 2].size(); ++i) {
			if (unit == data[NUM_OF_LETTERS_ENG * 2][i].name) return { NUM_OF_LETTERS_ENG * 2, i };

		}
		return { -1, -1 };
	}
	if ('A' <= unit[0] && unit[0] <= 'Z') {
		for (int i = 0; i < data[unit[0] - 'A'].size(); ++i) {
			if (unit == data[unit[0] - 'A'][i].name) return { unit[0] - 'A', i };

		}
		return { -1, -1 };
	}
	if ('0' <= unit[0] && unit[0] <= '9') {
		for (int i = 0; i < data[NUM_OF_LETTERS_ENG * 2 + 1].size(); ++i) {
			if (unit == data[NUM_OF_LETTERS_ENG * 2 + 1][i].name) return { NUM_OF_LETTERS_ENG * 2 + 1, i };

		}
		return { -1, -1 };
	}
	if (unit[0] == '-') {
		for (int i = 0; i < data[NUM_OF_LETTERS_ENG * 2 + 2].size(); ++i) {
			if (unit == data[NUM_OF_LETTERS_ENG * 2 + 2][i].name) return { NUM_OF_LETTERS_ENG * 2 + 2, i };

		}
		return { -1, -1 };
	}
}

int DynamicTable::getValue(pair <int, int> token) const {
	if (token.first != -1 && token.second != -1) {
		return data[token.first][token.second].value;

	}
	return -1;

}

void DynamicTable::setValue(pair <int, int> token, int value) {
	if (token.first != -1 && token.second != -1) {
		data[token.first][token.second].value = value;

	}
}