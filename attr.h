#pragma once
#include "data.h"
#include <string>
#include <list>

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

	std::string getName() {
		return Name;
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
		attr.clear();
	}

	std::list<Data*> getDatas() {
		return attr;
	}
};