#include "basesystem.h"

void BaseSystem::addBase(const std::string & name) {
	//未考虑重命名的情况
	DataBase *base = new DataBase;
	bases.insert(std::pair<std::string, DataBase*>(name, base));
	base_num++;
}

void BaseSystem::dropBase(std::string & base_name) {
	if (bases.find(base_name) == bases.end()) {
		std::cout << "未找到要删除的数据库" << std::endl;
	}
	else {
		auto post = find(bases_name.begin(), bases_name.end(), base_name);
		delete bases[base_name];
		bases.erase(base_name);
		bases_name.erase(post);
	}
}

void BaseSystem::showBase() {
	std::cout << "Database" << std::endl;
	for (auto it = bases.begin(); it != bases.end(); it++) {
		auto name = find(bases_name.begin(), bases_name.end(), it->first);
		if (name == bases_name.end()) {
			bases_name.push_back(it->first);
		}
	}
	sort(bases_name.begin(), bases_name.end());
	for (auto its = bases_name.begin(); its != bases_name.end(); its++) {
		std::cout << *its << std::endl;
	}
}

void BaseSystem::showTable(std::string& base_name) {
	std::cout << "Tables_in_" << base_name << std::endl;
	bases[base_name]->showTable();
}

void BaseSystem::show_table_colums(std::string& base_name, std::string& table_name) {
	bases[base_name]->show_table_colums(table_name);
}

void BaseSystem::dropTable(std::string &base_name,std::string & table_name){
	bases[base_name]->dropTable(table_name);
}