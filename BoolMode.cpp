#include "BoolMode.h"
BoolMode::BoolMode(){
	printA = 1;
	printAns = 2;
	simplify = 3;
	
	maxName = 1;
	maxTask = 3;
	
	up = 1;
	down = 2;
	left = 3;
	right = 4;
	selected = 5;
	esc = 6;
	
	inputBool = 1;
	doTask = 2;
	
	prevChoice = 0;
	title = "BOOL MODE: ";
	stage = inputBool;
	
	boolName[0] = "Nhap ham bool: ";
	boolName[1] = "1. B(A)";
	
	task[0] = "Lua chon tac vu: ";
	task[1] = "1. In B(A)";
	task[2] = "2. In B(Ans)";
	task[3] = "3. Rut gon";

 	PrintName();
}

BoolMode::~BoolMode(){

}

void BoolMode::ClearScreen(){
	for(int i = 1; i < 49; i++){
		for(int j = 5; j < 29; j++){
			DrawCharacter(i, j, white, blank);
		}
	}
}

void BoolMode::PrintName(){
	prevChoice = 1;
	choice = 1;
	
	ClearScreen();
	
	DrawCharacter(2, 6, yellow, header);
	DrawString(4, 6, green, title);	
	DrawString(2, 8, green, boolName[0]);
	DrawString(2, 10, red, boolName[1]);
}

void BoolMode::PrintTask(){
	prevChoice =1;
	choice = 1;
	
	ClearScreen();
	
	DrawCharacter(2, 6, yellow, header);
	DrawString(4, 6, green, title);	
	DrawString(2, 8, green, task[0]);
	DrawString(2, 10, red, task[1]);
	DrawString(2, 11, white, task[2]);
	DrawString(2, 12, white, task[3]);
}

void BoolMode::Input(){
	input = 0;
	if(GetAsyncKeyState(VK_UP)) input = up;
	else if(GetAsyncKeyState(VK_DOWN)) input = down;
	else if(GetAsyncKeyState(VK_LEFT)) input = left;
	else if(GetAsyncKeyState(VK_RIGHT)) input = right;
	else if(GetAsyncKeyState(VK_RETURN)){
		input = selected;
		cin.ignore();
	} 
	else if(GetAsyncKeyState(VK_ESCAPE)) input = esc;
	
}

bool BoolMode::Update(){
	if(input == up && choice > 1){
		prevChoice = choice;
		choice--;
	}
	else if(input == down){
		if((choice < maxName && stage == inputBool) || (choice < maxTask && stage == doTask)){
			prevChoice = choice;
			choice++;
		}
	}
	else if(input == left && stage == doTask){
		stage = inputBool;
		PrintName();
	}
	else if(input == right && stage == inputBool){
		stage = doTask;
		PrintTask();
	}
	else if(input == selected){
		if(stage == inputBool){
			boolFunction.InputKarnaugh();
			PrintName();
		}
		else{
			if(choice == printA) boolFunction.OutputKarnaugh();
			else if(choice == printAns) boolFunction.OutputResult();
			else if(choice == simplify){
				boolFunction.Simplify();
			}
			PrintTask();
		}
	}
	else if(input == esc){
		return true; 
	}
	return false;
}

void BoolMode::Render(){
	if(input == up || input == down){
		if(stage == inputBool){
			DrawString(2, prevChoice + 9, white, boolName[prevChoice]);
			DrawString(2, choice + 9, red, boolName[choice]);
		}
		else if(stage == doTask){
			DrawString(2, prevChoice +  9, white, task[prevChoice]);
			DrawString(2, choice + 9, red, task[choice]);
		}
	}
}

