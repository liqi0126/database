#include "basesystem.h"

void BaseSystem::addBase(const std::string & name) {
	//未考虑重命名的情况
	DataBase base;
	bases.insert(std::pair<std::string, DataBase>(name, base));
	base_num++;
}