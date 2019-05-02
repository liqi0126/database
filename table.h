#pragma once
#include "attr.h"
#include "whereclause.h"
#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
class Table {
protected:
	//����
	int row_num = 0;
	//������
	int attr_num = 0;
	//���д洢����Ϣ
	std::vector<Attr*> attrs;
	//���д������Ϣ,��ͬ������','���
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

	//��ʼ��Table��attrs��Ϣ��name��type)
	void init(std::string & _info);
	//Ϊattrs��������
	void addData(std::string & _info);

	//�ɵ���data�õ�һ��row
	std::string getRow(Data* data);
	//��attrs�õ�rows
	void setRows();
	//�ɵ�i�����Եõ�rows
	void setRows(int i);

	//��һ��row�ֽ�Ϊdata
	std::vector<Data*> separateRow(std::string row);
	//��rows�õ�attrs
	void setAttrs();

	//ѡ������
	void select(std::string & _info, std::string & Clause);

	//����,Ĭ�ϰ���������
	void Sort();

	//ɾ������
	void Delete(std::string & Clause);
	//��������
	void updateData(std::istringstream& _info);
		void show_table_colums();
};

