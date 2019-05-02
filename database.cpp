#include "database.h"
#include <sstream>
#include <iostream>

void DataBase::setTable(std::string & _info) {
	std::istringstream info(_info);
	std::string Tablename;
	getline(info, Tablename, '(');

	Table *table = new Table;
	table->init(_info);
	tables[Tablename] = table;
	table_num++;
}
void DataBase::updateData(std::string& _info)
{
	std::istringstream info(_info);
	std::string Tablename;
	info >> Tablename;
	tables[Tablename]->updateData(info);
}

void DataBase::addData(std::string & _info) {
	std::istringstream info(_info);
	std::string Tablename;
	info >> Tablename;
	getline(info, Tablename, ' ');
	getline(info, Tablename, '(');
	tables[Tablename]->addData(_info);
}

void DataBase::select(std::string & _info) {
	int x1 = _info.find("from");
	std::string name = _info.substr(x1 + 5);
	_info = _info.substr(0, x1 - 1);

	int x2 = name.find("WHERE");
	std::string whereClause;
	if (x2 != name.npos) {
		whereClause = name.substr(x2 + 6);
		name = name.substr(0, x2 - 1);
	}
	else {
		whereClause = "";
	}
	tables[name]->select(_info, whereClause);
}

void DataBase::Delete(std::string & _info) {
	int x1 = _info.find("FROM");
	std::string name = _info.substr(x1 + 5);

	int x2 = name.find("WHERE");
	std::string whereClause;
	if (x2 != name.npos) {
		whereClause = name.substr(x2 + 6);
		name = name.substr(0, x2 - 1);
	}
	else {
		whereClause = "";
	}
	tables[name]->Delete(whereClause);
}