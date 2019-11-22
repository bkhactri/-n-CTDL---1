#pragma once
#include "Draw.h"
#include "Vector.h"

struct VectorMode{
	// Name;
	int vectorACode;
	int vectorBCode;
	int vectorCCode;
	int vectorAnsCode;
	
	// Task;
	int printA;
	int printB;
	int printC;
	int printAns;
	int multiply;
	int numMultiply;
	
	int maxName;
	int maxTask;
	int up;
	int down;
	int left;
	int right;
	int selected;
	int esc;
	
	int inputVector;
	int doTask;
	Vector vector[5];
	
	string title;
	string vectorName[5];
	string task[7];
	int choice;
	int prevChoice;
	int input;
	int stage;
	
	VectorMode();
	~VectorMode();

	void ClearScreen();
	void PrintName();
	void PrintTask();
	void Input();
 	bool Update();
	void Render();
};

