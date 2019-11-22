#pragma once
#include "Draw.h"
#include "Bool.h"
#include<string>

struct BoolMode{
	// Name;
	int boolACode;
	int boolAnsCode;
	
	// Task;
	int printA;
	int printAns;
	int simplify;
	
	int maxName;
	int maxTask;
	int up;
	int down;
	int left;
	int right;
	int selected;
	int esc;
	
	int inputBool;
	int doTask;
	Bool boolFunction;
	
	string title;
	string boolName[2];
	string task[4];
	int choice;
	int prevChoice;
	int input;
	int stage;
	
	BoolMode();
	~BoolMode();

	void ClearScreen();
	
	void InputBool();
	void OutputBool();
	
	void PrintName();
	void PrintTask();
	
	void Input();
 	bool Update();
	void Render();
};

