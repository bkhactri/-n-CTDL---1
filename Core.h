#pragma once
#include <string>
using namespace std;
#include "Draw.h"
#include "Timer.h"
#include "SelectMode.h"

struct Program{
	string title;
	int mode;
	bool exitApp;
	Timer* timer;
	SelectMode* selectMode;
	
	Program();
	~Program();
	
	void Input();
	void Update();
	void Render();
	void Execute();
};



