#pragma once
#include "attr.h"
#include <map>
#include <string>
#include <vector>
#include <stack>

//从一行用逗号分隔的信息中找到第i个数据
std::string getData(std::string data, int i, char sper = ',');


class WhereClause {
	//whereClause运算优先级
	std::map<std::string, int> priority;
	//后缀表达式
	std::vector<std::string> Postfix;
public:
	WhereClause();
	//获得一个whereclause语句的后缀表达式
	void setPostfix(std::string _clause);
	//判断单个的judge语句对于数据data是否正确,attrs为数据属性
	bool Judge(std::string judge, const std::string& data, const std::vector<Attr*> & attrs);
	//计算后缀表达式，Arr为弹出的运算符，Oper为数据栈，data为当前数据，attrs为数据属性
	void Calc(std::stack<std::string> & Oper, std::string & Arr, const std::string & data,const std::vector<Attr*> & attrs);
	//判断数据data是否符合clause的条件,attrs为数据属性
	bool whereclause(const std::string & data, const std::string & _clause, const std::vector<Attr*> & attrs);
};

