#pragma once
#include "table.h"
#include <unordered_map>

class DataBase {
	int table_num = 0;
	std::unordered_map<std::string, Table> tables;
public:
	void setTable(std::string & _info);
	void addData(std::string & _info);
	void select(std::string & _info);
	void Delete(std::string & _info);
	void updateData(std::string& _info);
};