#pragma once
#include "table.h"
#include <unordered_map>

class DataBase {
	int table_num = 0;
	std::unordered_map<std::string, Table*> tables;
public:
	~DataBase() {
		for (auto it = tables.begin(); it != tables.end(); it++) {
			delete it->second;
		}
	}
	void setTable(std::string & _info);
	void addData(std::string & _info);
	void select(std::string & _info);
	void Delete(std::string & _info);
	void updateData(std::string& _info);
};