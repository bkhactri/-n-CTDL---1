#pragma once
#include "Draw.h"
#include "Matrix.h"

struct MatrixMode{
	// Name;
	int matrixACode;
	int matrixBCode;
	int matrixCCode;
	int matrixAnsCode;
	
	// Task;
	int printA;
	int printB;
	int printC;
	int printAns;
	int det;
	int inverse;
	int multiply;
	int rank;
	int system;
	
	int maxName;
	int maxTask;
	int up;
	int down;
	int left;
	int right;
	int selected;
	int esc;
	
	int inputMatrix;
	int doTask;
	Matrix matrix[5];
	
	string title;
	string matrixName[5];
	string task[10];
	int choice;
	int prevChoice;
	int input;
	int stage;
	
	MatrixMode();
	~MatrixMode();

	void ClearScreen();
	void PrintName();
	void PrintTask();
	void Input();
 	bool Update();
	void Render();
};
