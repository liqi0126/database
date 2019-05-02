#pragma once
#include "data.h"
#include <string>
#include <list>

bool datacompare(Data* a, Data* b);

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