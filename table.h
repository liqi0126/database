#pragma once
#include "attr.h"
#include "whereclause.h"
#include <vector>
#include <iostream>
#include <stack>

class Table {
protected:
	//行数
	int row_num = 0;
	//属性数
	int attr_num = 0;
	//以列存储的信息
	std::vector<Attr*> attrs;
	//以行储存的信息,不同属性用','间隔
	std::list<std::string> rows;
	//KEY
	int key = -1;
	//NOT NULL
	std::vector<int> not_null;
	//WhereClause
	WhereClause WC;
public:
	~Table() {
		for (auto it : attrs) {
			delete it;
		}
	}

	//初始化Table的attrs信息（name和type)
	void init(std::string & _info);
	//为attrs添加数据
	void addData(std::string & _info);

	//由单个data得到一行row
	std::string getRow(Data* data);
	//由attrs得到rows
	void setRows();
	//由第i个属性得到rows
	void setRows(int i);

	//将一行row分解为data
	std::vector<Data*> separateRow(std::string row);
	//将rows得到attrs
	void setAttrs();

	//选择数据
	void select(std::string & _info, std::string & Clause);

	//排序,默认按主键排序
	void Sort();

	//删除数据
	void Delete(std::string & Clause);
	//更新数据
	void updateData(std::istringstream& _info);
};

