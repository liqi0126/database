#include "ui.h"
#include <iostream>
#include <sstream>
#include <algorithm>

//正则化原则
//1.换行符视作空格
//2.多个连续空格只保留一个空格
//3.去除左括号、右括号、逗号、等号两侧的空格
//4.WHERE语句的括号两侧都保留一个空格
void UI::preProcess(std::string& sentence) {
	findKeywords(sentence);
	No_n(sentence);
	NoExtraSpace(sentence);
	return;
}


void UI::findKeywords(std::string& _info)
{
	std::string info(_info);
	transform(info.begin(), info.end(), info.begin(), ::toupper);
	std::string words[22] = { "CREATE","DATABASE","DATABASES","DROP","USE","SHOW","TABLE",
		"NOT","NULL","PRIMARY","KEY","TABLES","COLUMNS","FROM","INSERT",
		"INTO","VALUES","DELETE","WHERE","UPDATE","SET","SELECT" };
	for (int i = 0; i < 22; i++)
	{
		int x = -1;
		while (true)
		{
			x = info.find(words[i], x + 1);
			if (x == info.npos) break;
			_info.replace(x, words[i].size(), words[i]);
		}
	}


	return;
}
void UI::No_n(std::string& info)
{
	int x1 = -1;
	while (true)
	{
		x1 = info.find('\n', x1 + 1);
		if (x1 != info.npos) info[x1] = ' ';
		else break;
	}
}
void UI::NoExtraSpace(std::string& sentence)
{
	int x1 = -1;
	while (sentence[0] == ' ') sentence.erase(0, 1);
	while (sentence[sentence.size() - 1] == ' ')sentence.erase(sentence.size() - 1, 1);
	while (1)
	{
		x1 = sentence.find(' ', x1 + 1);
		if (x1 == sentence.npos)break;//找不到空格
		while (sentence[x1 + 1] == ' ')
		{
			sentence.erase(x1 + 1, 1);
		}
	}
	x1 = -1;
	while (1)
	{
		x1 = sentence.find('=', x1 + 1);
		if (x1 != sentence.npos)
		{
			if (x1 == 0 && sentence[x1 + 1] == ' ')
			{
				sentence.erase(x1 + 1, 1);
			}
			else if (x1 == sentence.size() - 1 && sentence[x1 - 1] == ' ')
			{
				sentence.erase(x1 - 1, 1);
			}
			else
			{
				if (sentence[x1 + 1] == ' ')
					sentence.erase(x1 + 1, 1);
				if (sentence[x1 - 1] == ' ')
					sentence.erase(x1 - 1, 1);
			}
		}
		else break;
	}
	x1 = -1;
	while (1)
	{
		x1 = sentence.find(',', x1 + 1);
		if (x1 != sentence.npos)
		{
			if (x1 == 0 && sentence[x1 + 1] == ' ')
			{
				sentence.erase(x1 + 1, 1);
			}
			else if (x1 == sentence.size() - 1 && sentence[x1 - 1] == ' ')
			{
				sentence.erase(x1 - 1, 1);
			}
			else
			{
				if (sentence[x1 + 1] == ' ')
					sentence.erase(x1 + 1, 1);
				if (sentence[x1 - 1] == ' ')
					sentence.erase(x1 - 1, 1);
			}
		}
		else break;
	}
	x1 = -1;
	int x2 = 0;
	while (1)
	{
		x2 = sentence.find("WHERE", 0);
		x1 = sentence.find('(', x1 + 1);
		if (x1 != sentence.npos)
		{
			if (x2 != sentence.npos&&x1 > x2)
			{
				if (sentence[x1 + 1] != ' ')sentence.insert(x1 + 1, 1, ' ');
				if (sentence[x1 - 1] != ' ')sentence.insert(x1, 1, ' ');
			}
			else if (x1 == 0 && sentence[x1 + 1] == ' ')
			{
				sentence.erase(x1 + 1, 1);
			}
			else if (x1 == sentence.size() - 1 && sentence[x1 - 1] == ' ')
			{
				sentence.erase(x1 - 1, 1);
			}
			else
			{
				if (sentence[x1 + 1] == ' ')
					sentence.erase(x1 + 1, 1);
				if (sentence[x1 - 1] == ' ')
					sentence.erase(x1 - 1, 1);
			}
		}
		else break;
	}
	x1 = -1;
	while (1)
	{
		x2 = sentence.find("WHERE", 0);
		x1 = sentence.find(')', x1 + 1);
		if (x1 != sentence.npos)
		{
			if (x2 != sentence.npos&&x1 > x2)
			{
				if (sentence[x1 + 1] != ' ')sentence.insert(x1 + 1, 1, ' ');
				if (sentence[x1 - 1] != ' ')sentence.insert(x1, 1, ' ');
			}
			else if (x1 == 0 && sentence[x1 + 1] == ' ')
			{
				sentence.erase(x1 + 1, 1);
			}
			else if (x1 == sentence.size() - 1 && sentence[x1 - 1] == ' ')
			{
				sentence.erase(x1 - 1, 1);
			}
			else
			{
				if (sentence[x1 + 1] == ' ')
					sentence.erase(x1 + 1, 1);
				if (sentence[x1 - 1] == ' ')
					sentence.erase(x1 - 1, 1);
			}
		}
		else break;
	}
}
std::stringstream UI::getCommand() {
	/*
	if (std::cin.rdbuf()->in_avail() == 0 || std::cin.rdbuf()->in_avail() == 1)
		std::cout << "mysql>";
	*/
	std::string sentence;
	getline(std::cin, sentence, ';');
	preProcess(sentence);
	std::stringstream myinput(sentence);
	return myinput;
}