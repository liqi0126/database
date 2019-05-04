#pragma once
#include "database.h"

class BaseSystem {
	int base_num = 0;
	DataBase * cur_base;
	std::unordered_map<std::string, DataBase*> bases;
public:
	~BaseSystem() {
		for (auto it = bases.begin(); it != bases.end(); it++) {
			delete it->second;
		}
	}
	
	void addBase(const std::string & name);

	void setBase(const std::string & name) {
		if (bases[name] == NULL) std::cout << "ERROR:未找到数据库'" << name << "'" << std::endl;
		else cur_base = bases[name];
	}

	void setTable(std::string & _info) {
		cur_base->setTable(_info);
	}

	void updateData(std::string& _info)
	{
		cur_base->updateData(_info);
	}
	void addData(std::string & _info) {
		cur_base->addData(_info);
	}

	void select(std::string & _info) {
		cur_base->select(_info);
	}

	void Delete(std::string & _info) {
		cur_base->Delete(_info);
	}

	void showBase();
	void showTable(std::string& base_name);
	void show_table_colums(std::string& table_name);
	void dropBase(std::string& base_name);
	void dropTable(std::string& table_name);
};