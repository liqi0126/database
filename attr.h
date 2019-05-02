#pragma once
#include "data.h"
#include <string>
#include <list>

bool datacompare(Data* a, Data* b);

/*
class DataCompare {
	bool operator() (Data* a, Data* b) {
		if (a->getType() == "INT") {
			IntData* inta = dynamic_cast<IntData*>(a);
			IntData* intb = dynamic_cast<IntData*>(b);
			return inta->getValue() < intb->getValue();
		}
		else if (a->getType() == "DOUBLE") {
			DoubleData* doublea = dynamic_cast<DoubleData*>(a);
			DoubleData* doubleb = dynamic_cast<DoubleData*>(b);
			return doublea->getValue() < doubleb->getValue();
		}
		return a->getData() < b->getData();
	}
}datacompare;
*/

class Attr {
protected:
	std::string Type;
	std::string Name;
	std::list<Data*> attr;
	bool Key = false;
	bool NotNull = false;
public:
	Attr(std::string _Name, std::string _Type) {
		Name = _Name;
		Type = _Type;
	}

	~Attr() {
		for (auto it : attr) {
			delete it;
		}
	}

	std::string getName() {
		return Name;
	}

	std::string getType() {
		return Type;
	}

	void setKey() {
		Key = true;
	}

	void notNull() {
		NotNull = true;
	}

	void addData(Data* data) {
		attr.push_back(data);
	}

	void cleanData() {
		for (auto it : attr)
			delete it;
		attr.clear();
	}

	std::list<Data*> getDatas() {
		return attr;
	}

	void Sort() {
		attr.sort(datacompare);
	}
};