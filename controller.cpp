#include "controller.h"
#include <sstream>

void Controller::operate() {
	while (true) {
		std::stringstream myinput = ui.getCommand();
		static std::string order;
		//输入命令

		myinput >> order;
		//创建数据库或表单
		if (order == "CREATE") {
			myinput >> order;
			if (order == "DATABASE") {
				getline(myinput, order, ' ');
				getline(myinput, order);
				system.addBase(order);
			}
			else if (order == "TABLE") {
				getline(myinput, order, ' ');
				getline(myinput, order);
				system.setTable(order);
			}
			else {
				std::cout << "未识别的命令" << std::endl;
			}
		}
		//删除数据库
		else if (order == "DROP") {
			getline(myinput, order, ' ');
			getline(myinput, order);
			system.dropBase(order);
		}
		//切换数据库
		else if (order == "USE") {
			getline(myinput, order, ' ');
			getline(myinput, order);
			system.setBase(order);
		}
		//列出所有数据库及其包含的所有表名
		else if (order == "INSERT") {
			getline(myinput, order, ' ');
			getline(myinput, order);
			system.addData(order);
		}
		else if (order == "SHOW") {

		}
		//表的数据删除
		else if (order == "DELETE") {
			getline(myinput, order, ' ');
			getline(myinput, order);
			system.Delete(order);
		}
		//表的数据修改
		else if (order == "UPDATE") {
			getline(myinput, order);
			system.updateData(order);
		}
		//表的查询
		//实现whereClauses语句
		else if (order == "SELECT") {
			getline(myinput, order, ' ');
			getline(myinput, order);
			system.select(order);
		}
		else if (order == "QUIT") {
			break;
		}
		else {
			std::cout << "未识别的命令" << std::endl;
		}
	}
}