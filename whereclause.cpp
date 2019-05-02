#include "whereclause.h"
#include <sstream>
//从一行用逗号分隔的信息中找到第i个数据
std::string getData(std::string data, int i) {
	int x1 = -1;
	while (i--)
		x1 = data.find(',', x1 + 1);
	int x2 = data.find(',', x1 + 1);
	if (x2 == data.npos)
		x2 = data.length();

	return data.substr(x1 + 1, x2 - x1 - 1);
}

WhereClause::WhereClause() {
	//默认优先级
	priority.insert(std::pair<std::string, int>("(", 0));
	priority.insert(std::pair<std::string, int>(")", -1));
	priority.insert(std::pair<std::string, int>("AND", -2));
	priority.insert(std::pair<std::string, int>("OR", -3));
}

void WhereClause::setPostfix(std::string _clause) {
	Postfix.clear();
	std::istringstream clause(_clause);
	std::stack<std::string> operStack;
	std::string Arr;
	while (clause >> Arr) {
		if (priority.find(Arr) != priority.end()) {
			if (priority[Arr] == -1) {
				while (priority[operStack.top()] != 0) {
					Postfix.push_back(operStack.top());
					operStack.pop();
				}
				operStack.pop();
			}
			else if (operStack.empty() ||
				operStack.top() == "(" ||
				priority[Arr] > priority[operStack.top()]) {
				operStack.push(Arr);
			}
			else {
				Postfix.push_back(operStack.top());
				operStack.pop();
				operStack.push(Arr);
			}
		}
		else {
			Postfix.push_back(Arr);
		}
	}
	while (!operStack.empty()) {
		Postfix.push_back(operStack.top());
		operStack.pop();
	}
}

bool WhereClause::Judge(std::string judge, const std::string & data, const std::vector<Attr*> & attrs) {
	if (judge == "TRUE") {
		return true;
	}
	else if (judge == "FALSE") {
		return false;
	}
	else {
		int temp = judge.find('>');
		if (temp == judge.npos)
			temp = judge.find('<');
		if (temp == judge.npos)
			temp = judge.find('=');

		std::string left = judge.substr(0, temp);
		std::string right = judge.substr(temp + 1);

		int attr_num = attrs.size();
		for (int i = 0; i < attr_num; i++) {
			if (attrs[i]->getName() == left) {
				left = getData(data, i);
			}
			if (attrs[i]->getName() == right) {
				right = getData(data, i);
			}
		}

		if (judge[temp] == '=') {
			return left == right;
		}
		else {
			int L = stoi(left), R = stoi(right);
			if (judge[temp] == '>')
				return (L > R) ? true : false;
			else {
				return (L < R) ? true : false;
			}
		}
	}
}

void WhereClause::Calc(std::stack<std::string> & Oper, std::string & Arr, const std::string & data, const std::vector<Attr*> & attrs) {
	std::string oper1 = Oper.top();
	Oper.pop();
	std::string oper2 = Oper.top();
	Oper.pop();
	bool judge, judge1 = Judge(oper1, data, attrs), judge2 = Judge(oper2, data, attrs);
	if (Arr == "AND") {
		judge = judge1 && judge2;
	}
	else {
		judge = judge1 || judge2;
	}
	if (judge) {
		Oper.push("TRUE");
	}
	else {
		Oper.push("FALSE");
	}
}

bool WhereClause::whereclause(const std::string & data, const std::string & _clause, const std::vector<Attr*> & attrs) {
	if (_clause == "") {
		return true;
	}

	//转为后缀表达式
	//将后缀表达式设为静态并进行判断，以防止对同一表达式反复构造
	static std::string copy = _clause;
	if (Postfix.size() == 0 || copy != _clause) {
		setPostfix(_clause);
	}

	//后缀表达式的计算
	std::stack<std::string> Oper;
	for (size_t i = 0; i < Postfix.size(); i++) {
		if (priority.find(Postfix[i]) != priority.end()) {
			Calc(Oper, Postfix[i], data,attrs);
		}
		else {
			Oper.push(Postfix[i]);
		}
	}

	if (Judge(Oper.top(), data, attrs)) {
		return true;
	}
	else {
		return false;
	}
}