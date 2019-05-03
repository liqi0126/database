#pragma once
#include "ui.h"
#include "basesystem.h"
#include <unordered_map>

class Controller {
	UI ui;
	BaseSystem system;
public:
	//实现Base的各种功能
	void operate();
};