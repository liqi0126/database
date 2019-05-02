#include "ui.h"
#include <iostream>
#include <sstream>

//����ԭ��
//1.���з������ո�
//2.��������ո�ֻ����һ���ո�
//3.ȥ�������š������š����š��Ⱥ�����Ŀո�
//4.WHERE�����������඼����һ���ո�
void UI::preProcess(std::string& sentence) {
	int x1 = -1;
	while (1)
	{
		x1 = sentence.find('\n', x1 + 1);
		if (x1 != sentence.npos) sentence[x1] = ' ';
		else break;
	}
	x1 = -1;
	while (sentence[0] == ' ') sentence.erase(0, 1);
	while (sentence[sentence.size() - 1] == ' ')sentence.erase(sentence.size() - 1, 1);
	while (1)
	{
		x1 = sentence.find(' ', x1 + 1);
		if (x1 == sentence.npos)break;//�Ҳ����ո�
		if (x1 == sentence.size() - 1)//�ҵ��Ŀո������һ���ַ�
		{
			sentence.erase(x1, 1);
			break;
		}
		while (x1 + 1 < sentence.size() && sentence[x1 + 1] == ' ')
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
	return;
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