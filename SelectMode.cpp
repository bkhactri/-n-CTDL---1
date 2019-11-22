#include "SelectMode.h"

SelectMode::SelectMode(){
	up = 1;
	down = 2;
	selected = 3;
	esc = 4;
	
	Bool = 1;
	Vector = 2;
	Matrix = 3;
	maxChoice = 3;
	
	selectBoolStage = 1;
	selectVectorStage = 2;
	selectMatrixStage = 3;
	
	stage = selectModeStage;
	title = "SELECT MODE: ";
	mode[1] = "1. Bool";
	mode[2] = "2. Vector";
	mode[3] = "3. Matrix";
	
	choice = 1;
	input = 0;
	Print();
}

SelectMode::~SelectMode(){

}

void SelectMode::Print(){ // in menu
	for(int i = 2; i < 49; i++){
		for(int j = 6; j < 29; j++){
			DrawCharacter(i, j, white, blank);
		}
	}
	
	for(int i = 0; i < 50; i++){
		DrawCharacter(i, 0, 15, border);
		DrawCharacter(i, 29, 15, border);
		DrawCharacter(i, 4, 15, border);
	}
	for(int i = 0; i < 30; i++){
		DrawCharacter(50, i, 15, border);
		DrawCharacter(0, i, 15, border);
	}
	
	DrawCharacter(2, 6, yellow, header);
	DrawString(4, 6, green, title);	
	DrawString(2, 8, red, mode[1]);
	DrawString(2, 9, white, mode[2]);
	DrawString(2, 10, white, mode[3]);
}

void SelectMode::Input(){
	if(stage == selectModeStage){
		input = 0;
		if(GetAsyncKeyState(VK_UP)) input = up;
		else if(GetAsyncKeyState(VK_DOWN)) input = down;
		else if(GetAsyncKeyState(VK_RETURN)){
			input = selected;
			cin.ignore();
		}
		else if(GetAsyncKeyState(VK_ESCAPE)) input = esc;
	}
	else if(stage == selectBoolStage){
		boolMode->Input();
	}
	else if(stage == selectVectorStage){
		vectorMode->Input();
	}
	else if(stage == selectMatrixStage){
		matrixMode->Input();
	}
}

void SelectMode::Update(){
	if(input == esc){
		GotoXY(50, 50);
		exit(0);
	}
	if(stage == selectModeStage){
		if(input == up && choice > 1){
			prevChoice = choice;
			choice--;
		}
		else if(input == down && choice < maxChoice){
			prevChoice = choice;
			choice++;
		}
		else if(input == selected){
			stage = choice;
			choice = 1;
			prevChoice = 0;
			if(stage == selectBoolStage) boolMode = new BoolMode;
			else if(stage == selectVectorStage) vectorMode = new VectorMode;
			else if(stage == selectMatrixStage) matrixMode = new MatrixMode;
		}
	}
	else if(stage == selectBoolStage){
		if(boolMode->Update()){
			stage = selectModeStage;
			Print();
		}
	}
	else if(stage == selectVectorStage){
		if(vectorMode->Update()){
			stage = selectModeStage;
			Print();
		}
	}
	else if(stage == selectMatrixStage){
		if(matrixMode->Update()){
			stage = selectModeStage;
			Print();
		}
	}
}

void SelectMode::Render(){
	if(stage == selectModeStage){
		if(input == up || input == down){
			DrawString(2, prevChoice + 7, white, mode[prevChoice]);
			DrawString(2, choice + 7, red, mode[choice]);
		}
		else if(input == selected){
			
		}
	}
	else if(stage == selectBoolStage){
		boolMode->Render();
	}
	else if(stage == selectVectorStage){
		vectorMode->Render();
	}
	else if(stage == selectMatrixStage){
		matrixMode->Render();
	}
}
