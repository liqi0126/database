#include "table.h"
#include <sstream>
#include <utility>
#include <iostream>
#include <algorithm>
#include <list>
#include <map>

//将str中所有的origin替换为sub
std::string replaceAll(std::string str, std::string origin, std::string sub) {
	int L1 = origin.length(), L2 = sub.length();
	int x;
	while ((x = str.find(origin)) != str.npos) {
		str.replace(x, L1, sub);
	}
	return str;
}

void Table::init(std::string & _info) {
	std::istringstream info(_info);
	std::string data;
	getline(info, data, '(');
	while (getline(info, data, ',')) {
		if (*data.rbegin() == ')') data.pop_back();
		//设置主键
		bool iskey = false;
		int x = data.find("PRIMARY KEY");
		if (x != data.npos) {
			int x1 = data.find_first_of('(');
			int x2 = data.find_first_of(')');
			std::string name = data.substr(x1 + 1, x2 - x1 - 1);
			for (size_t i = 0; i < attrs.size(); i++) {
				if (attrs[i]->getName() == name) {
					key = i;
					iskey = true;
					break;
				}
			}
			continue;
		}

		bool notnull = false;
		x = data.find("NOT NULL");
		if (x != data.npos) {
			//设置非空项
			notnull = true;
			not_null.push_back(attr_num);
			//删除NOT NULL
			data.erase(x - 1, 9);
		}

		//添加属性
		x = data.find(' ');
		std::string name = data.substr(0, x);
		std::string type = data.substr(x + 1);
		Attr *attr = new Attr(name, type);
		if(notnull)	attr->notNull();
		if (iskey) attr->setKey();
		attrs.push_back(attr);
		attr_num++;
	}
}

void Table::addData(std::string & _info) {
	row_num++;
	std::istringstream info(_info);
	std::string data;
	getline(info, data, '(');
	getline(info, data, ')');

	std::vector<int> attrId;
	int x;
	std::string name;
	//添加属性
	while ((x = data.find_first_of(',')) != data.npos) {
		name = data.substr(0, x);
		data = data.substr(x + 1);

		for (int i = 0; i < attr_num; i++) {
			if (attrs[i]->getName() == name) {
				attrId.push_back(i);
				break;
			}
		}
	}
	for (int i = 0; i < attr_num; i++) {
		if (attrs[i]->getName() == data) {
			attrId.push_back(i);
			break;
		}
	}

	//检查notnull
	for (auto it : not_null) {
		if (find(attrId.begin(), attrId.end(), it) == attrId.end()) {
			std::cout << attrs[it]->getName() << "不允许为空"<< std::endl;
			return;
		}
	}

	//数据
	std::string new_row;
	std::vector<Data*> new_attr;
	getline(info, data, '(');
	getline(info, data, ')');
	for (int i = 0; i < attr_num; i++) {
		//查找是否有相应的数据
		size_t j;
		for (j = 0; j < attrId.size(); j++) {
			if (attrId[j] == i) {
				break;
			}
		}
		//赋值
		if (j != attrId.size()) {
			new_row += getData(data, j);
			Data *p;
			if (attrs[i]->getType() == "INT") { p = new IntData(getData(data, j)); }
			else if (attrs[i]->getType() == "DOUBLE") { p = new DoubleData(getData(data, j)); }
			else { p = new Data(getData(data, j)); }
			new_attr.push_back(p);
		}
		else {
			Data *p;
			if (attrs[i]->getType() == "INT") { p = new IntData(""); }
			else if (attrs[i]->getType() == "DOUBLE") { p = new DoubleData(""); }
			else { p = new Data(""); }
			new_attr.push_back(p);
		}
		if (i != attr_num - 1)
			new_row += ",";
	}
	rows.push_back(new_row);

	//加入到attr中
	for (size_t i= 0; i < new_attr.size(); i++) {
		if (i == 0) {
			new_attr[i]->setSuc(new_attr[i + 1]);
			attrs[i]->addData(new_attr[i]);
		}
		else if (i == new_attr.size() - 1) {
			new_attr[i]->setPre(new_attr[i - 1]);
			attrs[i]->addData(new_attr[i]);
		}
		else {
			new_attr[i]->setPre(new_attr[i - 1]);
			new_attr[i]->setSuc(new_attr[i + 1]);
			attrs[i]->addData(new_attr[i]);
		}
	}
}

std::string Table::getRow(Data* data) {
	while (data->getPre() != NULL)
		data = data->getPre();
	
	std::string row;

	while (data->getSuc() != NULL) {
		row += data->getData() + ",";
		data = data->getSuc();
	}
	row += data->getData();
	
	return row;
}

void Table::setRows() {
	//清除rows
	rows.clear();
	std::list<Data*> temp = attrs[key]->getDatas();
	for (auto it : temp) {
		rows.push_back(getRow(it));
	}
}

void Table::setRows(int i) {
	rows.clear();
	std::list<Data*> temp = attrs[i]->getDatas();
	for (auto it : temp) {
		rows.push_back(getRow(it));
	}
}

std::vector<Data*> Table::separateRow(std::string _row) {
	std::istringstream row(_row);
	std::vector<Data*> datas;
	std::string data;
	int i = 0;
	while (getline(row, data, ',')) {
		Data * p;
		if (attrs[i]->getType() == "INT") { p = new IntData(data); }
		else if (attrs[i]->getType() == "DOUBLE") { p = new DoubleData(data); }
		else { p = new Data(data); }
		datas.push_back(p);
		i++;
	}
	//建立连接
	for (size_t i = 0; i < datas.size(); i++) {
		if (i == 0) {
			datas[i]->setSuc(datas[i + 1]);
		}
		else if (i == datas.size() - 1) {
			datas[i]->setPre(datas[i - 1]);
		}
		else {
			datas[i]->setPre(datas[i - 1]);
			datas[i]->setSuc(datas[i + 1]);
		}
	}
	return datas;
}

void Table::setAttrs() {
	for (auto it : attrs) {
		it->cleanData();
	}

	for (auto it : rows) {
		std::vector<Data*> datas = separateRow(it);
		for (int i = 0; i < attr_num; i++) {
			attrs[i]->addData(datas[i]);
		}
	}
}

void Table::select(std::string & _info, std::string & Clause) {
	Sort();
	if (_info == "*") {
		for (auto it = attrs.begin(); it != attrs.end(); it++) {
			if(it != --attrs.end())
				std::cout << (*it)->getName() << '\t';
			else {
				std::cout << (*it)->getName();
			}
		}
		std::cout << std::endl;

		for (auto it : rows) {
			if (WC.whereclause(it, Clause,attrs))
				std::cout << replaceAll(it,",","\t") << std::endl;
		}
	}
	else {
		std::istringstream info(_info);
		std::vector<std::string> names;
		std::string name;

		while (getline(info, name, ',')) {
			names.push_back(name);
		}

		std::vector<int> output;
		for (size_t i = 0; i < names.size(); i++) {
			for (int j = 0; j < attr_num; j++) {
				if (attrs[j]->getName() == names[i]) {
					output.push_back(j);
				}
			}
		}
		
		for (auto it = names.begin(); it != names.end(); it++) {
			if (it != --names.end())
				std::cout << *it << '\t';
			else {
				std::cout << *it;
			}
		}
		std::cout << std::endl;

		for (auto row : rows) {
			if (WC.whereclause(row, Clause,attrs)) {
				size_t i = 0;
				for (; i < output.size() - 1; i++) {
					std::cout << getData(row, output[i]) << "\t";
				}
				std::cout << getData(row, output[i]) << std::endl;
			}
		}
	}
}

void Table::Sort() {
	attrs[key]->Sort();
	setRows();
	setAttrs();
}

void Table::Delete(std::string & Clause) {
	for (auto it = rows.begin(); it != rows.end();) {
		if (WC.whereclause(*it, Clause,attrs)) {
			it = rows.erase(it);
			row_num--;
		}
		else {
			it++;
		}
	}
	setAttrs();
}

void Table::updateData(std::istringstream& info)
{
	//UPDATE xxtable SET attrName = attrValue WHERE XXXXX;
	std::string data;
	std::string value;
	info >> data;//"SET"
	info >> std::ws;
	getline(info, data, '=');
	int index = 0;
	while (attrs[index]->getName() != data && index < attr_num)index++;
	if (index == attr_num) std::cout << "error" << std::endl;
	info >> std::ws;//'='
	info >> value;//得到value
	info >> data;//"WHERE"
	if (data != "WHERE") data = "";
	else getline(info, data);//得到条件语句
	//todo:实现WHERECLAUSE
	for (std::list<std::string>::iterator it = rows.begin(); it != rows.end(); it++)
	{
		if (WC.whereclause(*it, data, attrs))//遍历链表，根据WHERECLAUSE找到行
		{
			std::string& tmprow = *it;
			if (attrs.size() > 1) {
				int x1 = -1;
				for (int kk = 0; kk < index; kk++)
				{
					x1 = tmprow.find(',', x1 + 1);
				}
				int x2 = tmprow.find(',', x1 + 1);
				if (x2 == tmprow.npos) x2 = tmprow.size();
				tmprow.replace(x1 + 1, x2 - x1 - 1, value);
			}
			else tmprow = value;
		}
	}
	setAttrs();
}

void Table::show_table_colums() {
	std::cout << "Field   Type    Null    Key Default Extra" << std::endl;
	for (int i = 0; i < attr_num; i++) {
		std::cout << attrs[i]->getName() << " ";
		std::string type = attrs[i]->getType();
		transform(type.begin(), type.end(), type.begin(), ::tolower);
		if (type == "int") {
			std::cout << "int(11) ";
		}
		else {
			if (type == "char")
				std::cout << "char(1) ";
			else std::cout << type << "  ";
		}
		auto inotnull = find(not_null.begin(), not_null.end(), i);
		if (inotnull != not_null.end()) {
			std::cout << "NO  ";
		}
		else std::cout << "YES ";
		if (i == key) {
			std::cout << "PRI NULL" << std::endl;
		}
		else std::cout << "    NULL" << std::endl;
	}
}