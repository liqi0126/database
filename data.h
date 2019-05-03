#pragma once
#include <string>
#include <sstream>

//将str中所有的origin替换为sub
std::string replaceAll(std::string str, std::string origin, std::string sub);

class Data {
protected:
	std::string data;
	Data* pre = NULL;
	Data* suc = NULL;
public:
	Data(std::string _data) {
		data = _data;
	}
	//数据的设置
	virtual void setData(std::string _data) {
		data = _data;
	}
	//数据的获取
	virtual std::string getData() {
		return data;
	}
	//类型的识别
	virtual std::string getType() {
		return "CHAR";
	}

	virtual std::string showData() {
		if (data == "") {
			return "NULL";
		}
		else {
			return replaceAll(data,"\"","");
		}
	}

	void setPre(Data *_pre) {
		pre = _pre;
	}

	void setSuc(Data *_suc) {
		suc = _suc;
	}

	Data* getPre() {
		return pre;
	}

	Data* getSuc() {
		return suc;
	}
};

class IntData : public Data {
protected:
	int value = 0;
public:
	IntData(std::string _data) : Data(_data) {
		if(_data != "")
			value = stoi(data);
	}

	void setData(std::string _data) {
		data = _data;
		if (_data != "")
			value = stoi(data);
	}

	std::string showData() {
		if (data == "") {
			return "NULL";
		}
		else {
			return data;
		}
	}

	int getValue() {
		return value;
	}

	std::string getType() {
		return "INT";
	}
};

class DoubleData : public Data {
protected:
	double value = 0;
public:
	DoubleData(std::string _data) : Data(_data) {
		if (_data != "") {
			std::stringstream data(_data);
			data >> value;
		}
	}

	void setData(std::string _data) {
		data = _data;
		if (_data != "") {
			std::stringstream data(_data);
			data >> value;
		}
	}

	std::string showData();

	double getValue() {
		return value;
	}

	std::string getType() {
		return "DOUBLE";
	}
};

//得到data这一行的第i个数据
Data* get_Data_i(Data* data, int i);