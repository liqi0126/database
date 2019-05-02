#pragma once
#include <string>

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
	int value;
public:
	IntData(std::string _data) : Data(_data) {
		value = stoi(data);
	}
};

class BoolData : public Data {
	bool value;
public:
	BoolData(std::string _data) : Data(_data) {
		value = (data == "TRUE") ? true : false;
	}
};