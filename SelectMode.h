#pragma once
#include<string.h>
using namespace std;

#include "Draw.h"
#include "VectorMode.h"
#include "MatrixMode.h"
#include "BoolMode.h"

struct SelectMode{
	int up;
	int down;
	int selected;
	int esc;
	
	int Bool;
	int Vector;
	int Matrix;
	int maxChoice;
	
	int selectModeStage;
	int selectBoolStage;
	int selectVectorStage;
	int selectMatrixStage;
	
	
	string title;
	string mode[4];
	int prevChoice;
	int choice;
	int input;
	int stage;
	BoolMode* boolMode;
	VectorMode* vectorMode;
	MatrixMode* matrixMode;
	
	SelectMode();
	~SelectMode();
	
	void Print();
	
	void Input();
	void Update();
	void Render();
};
