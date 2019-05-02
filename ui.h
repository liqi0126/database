#pragma once
#include <string>

class UI {
public:
	//这里最好把正则化的各个功能分装成接口，然后再统一正则化
	void preProcess(std::string&);
	std::stringstream getCommand();
};