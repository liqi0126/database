#pragma once
#include <string>

class UI {
public:
	//这里最好把正则化的各个功能分装成接口，然后再统一正则化
	void findKeywords(std::string&);//不区分大小写地找到关键词，并全改为大写
	void No_n(std::string&);//无视读入的换行符
	void NoExtraSpace(std::string&);//去除多余的空格

	void preProcess(std::string&);
	std::stringstream getCommand();
};