#include "VectorMode.h"
VectorMode::VectorMode(){
	vectorACode = 1;
	vectorBCode = 2;
	vectorCCode = 3;
	vectorAnsCode = 4;
	
	printA = 1;
	printB = 2;
	printC = 3;
	printAns = 4;
	multiply = 5;
	numMultiply = 6;
	
	maxName = 3;
	maxTask = 6;
	
	up = 1;
	down = 2;
	left = 3;
	right = 4;
	selected = 5;
	esc = 6;
	
	inputVector = 1;
	doTask = 2;
	
	choice = vectorACode;
	prevChoice = 0;
	title = "VECTOR MODE: ";
	stage = inputVector;
	
	vectorName[0] = "Nhap vector: ";
	vectorName[1] = "1. V(A)";
	vectorName[2] = "2. V(B)";
	vectorName[3] = "3. V(C)";
	
	task[0] = "Lua chon tac vu: ";
	task[1] = "1. In V(A)";
	task[2] = "2. In V(B)";
	task[3] = "3. In V(C)";
	task[4] = "4. In V(Ans)";
	task[5] = "5. Tong hai vector";
	task[6] = "6. Nhan vector voi mot so";

 	PrintName();
}

VectorMode::~VectorMode(){
	
}

void VectorMode::ClearScreen(){
	for(int i = 2; i < 49; i++){
		for(int j = 6; j < 29; j++){
			DrawCharacter(i, j, white, blank);
		}
	}
}
void VectorMode::PrintName(){
	prevChoice =1;
	choice = 1;
	
	ClearScreen();
	
	DrawCharacter(2, 6, yellow, header);
	DrawString(4, 6, green, title);	
	DrawString(2, 8, green, vectorName[0]);
	DrawString(2, 10, red, vectorName[1]);
	DrawString(2, 11, white, vectorName[2]);
	DrawString(2, 12, white, vectorName[3]);
	DrawString(2, 13, white, vectorName[4]);
	
}

void VectorMode::PrintTask(){
	prevChoice =1;
	choice = 1;
	
	ClearScreen();
	
	DrawCharacter(2, 6, yellow, header);
	DrawString(4, 6, green, title);	
	DrawString(2, 8, green, task[0]);
	DrawString(2, 10, red, task[1]);
	DrawString(2, 11, white, task[2]);
	DrawString(2, 12, white, task[3]);
	DrawString(2, 13, white, task[4]);
	DrawString(2, 14, white, task[5]);
	DrawString(2, 15, white, task[6]);
}

void VectorMode::Input(){
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

bool VectorMode::Update(){
	if(input == up && choice > 1){
		prevChoice = choice;
		choice--;
	}
	else if(input == down){
		if((choice < maxName && stage == inputVector) || (choice < maxTask && stage == doTask)){
			prevChoice = choice;
			choice++;
		}
	}
	else if(input == left && stage == doTask){
		stage = inputVector;
		PrintName();
	}
	else if(input == right && stage == inputVector){
		stage = doTask;
		PrintTask();
	}
	else if(input == selected){
		if(stage == inputVector){
			if(choice == vectorACode) InputVector(vector[vectorACode]);
			else if(choice == vectorBCode) InputVector(vector[vectorBCode]);
			else if(choice == vectorCCode) InputVector(vector[vectorCCode]);
			PrintName();
		}
		else{
			if(choice == printA) OutputVector(vector[vectorACode]);
			else if(choice == printB) OutputVector(vector[vectorBCode]);
			else if(choice == printC) OutputVector(vector[vectorCCode]);
			else if(choice == printAns) OutputVector(vector[vectorAnsCode]);
			else if(choice == multiply){
				ClearScreen();
				DrawString(2, 6, white, "Nhap ten vector 1: ");
				string name1;
				cin >> name1;
				cin.ignore();
				DrawString(2, 7, white, "Nhap ten vector 2: ");
				string name2;
				cin >> name2;
				cin.ignore();
				vector[vectorAnsCode] = PlusTwoVector(vector[GetVector(name1)], vector[GetVector(name2)]);
				if(vector[vectorAnsCode].count != -1){
					OutputVector(vector[vectorAnsCode]);
				}
				else DrawString(2, 8, white, "So luong thanh phan 2 vector khac nhau");
			}
			else if(choice == numMultiply){
				ClearScreen();
				DrawString(2, 6, white, "Nhap ten vector: ");
				string name;
				cin >> name;
				cin.ignore();
				DrawString(2, 7, white, "Nhap so: ");
				float num;
				cin >> num;
				cin.ignore();
				vector[vectorAnsCode] = MultiplyVectorWithNumber(vector[GetVector(name)], num);
				OutputVector(vector[vectorAnsCode]);
			}
			getch();
			fflush(stdin);
			GetAsyncKeyState(VK_RETURN);
			PrintTask();
		}
	}
	else if(input == esc){
		return true; 
	}
	return false;
}

void VectorMode::Render(){
	if(input == up || input == down){
		if(stage == inputVector){
			DrawString(2, prevChoice +  9, white, vectorName[prevChoice]);
			DrawString(2, choice + 9, red, vectorName[choice]);
		}
		else if(stage == doTask){
			DrawString(2, prevChoice +  9, white, task[prevChoice]);
			DrawString(2, choice + 9, red, task[choice]);
		}
	}
}

