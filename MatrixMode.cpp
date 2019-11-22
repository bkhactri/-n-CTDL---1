#include "MatrixMode.h"
MatrixMode::MatrixMode(){
	matrixACode = 1;
	matrixBCode = 2;
	matrixCCode = 3;
	matrixAnsCode = 4;
	
	printA = 1;
	printB = 2;
	printC = 3;
	printAns = 4;
	det = 5;
	inverse = 6;
	multiply = 7;
	rank = 8;
	system = 9;
	
	maxName = 3;
	maxTask  = 9;
	
	up = 1;
	down = 2;
	left = 3;
	right = 4;
	selected = 5;
	esc = 6;
	
	inputMatrix = 1;
	doTask = 2;
	
	choice = matrixACode;
	prevChoice = 0;
	title = "MATRIX MODE: ";
	stage = inputMatrix;
	
	matrixName[0] = "Nhap ma tran: ";
	matrixName[1] = "1. M(A)";
	matrixName[2] = "2. M(B)";
	matrixName[3] = "3. M(C)";
	
	task[0] = "Lua chon tac vu: ";
	task[1] = "1. In M(A)";
	task[2] = "2. In M(B)";
	task[3] = "3. In M(C)";
	task[4] = "4. In M(Ans)";
	task[5] = "5. Tinh dinh thuc ma tran";
	task[6] = "6. Nghich dao ma tran";
	task[7] = "7. Tich hai ma tran";
	task[8] = "8. Tim hang ma tran";
	task[9] = "9. He phuong trinh tuyen tinh";
	
 	PrintName();
}

MatrixMode::~MatrixMode(){
	
}

void MatrixMode::ClearScreen(){
	for(int i = 2; i < 49; i++){
		for(int j = 6; j < 29; j++){
			DrawCharacter(i, j, white, blank);
		}
	}
}
void MatrixMode::PrintName(){
	prevChoice =1;
	choice = 1;
	
	ClearScreen();
	
	DrawCharacter(2, 6, yellow, header);
	DrawString(4, 6, green, title);	
	DrawString(2, 8, green, matrixName[0]);
	DrawString(2, 10, red, matrixName[1]);
	DrawString(2, 11, white, matrixName[2]);
	DrawString(2, 12, white, matrixName[3]);
	DrawString(2, 13, white, matrixName[4]);
	
}

void MatrixMode::PrintTask(){
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
	DrawString(2, 16, white, task[7]);
	DrawString(2, 17, white, task[8]);
	DrawString(2, 18, white, task[9]);
	
}

void MatrixMode::Input(){
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

bool MatrixMode::Update(){
	if(input == up && choice > 1){
		prevChoice = choice;
		choice--;
	}
	else if(input == down){
		if((choice < maxName && stage == inputMatrix) || (choice < maxTask && stage == doTask)){
			prevChoice = choice;
			choice++;
		}
	}
	else if(input == left && stage == doTask){
		stage = inputMatrix;
		PrintName();
	}
	else if(input == right && stage == inputMatrix){
		stage = doTask;
		PrintTask();
	}
	else if(input == selected){
		if(stage == inputMatrix){
			if(choice == matrixACode) InputMatrix(matrix[matrixACode]);
			else if(choice == matrixBCode) InputMatrix(matrix[matrixBCode]);
			else if(choice == matrixCCode) InputMatrix(matrix[matrixCCode]);
			PrintName();
		}
		else{
			if(choice == printA) OutputMatrix(matrix[matrixACode]);
			else if(choice == printB) OutputMatrix(matrix[matrixBCode]);
			else if(choice == printC) OutputMatrix(matrix[matrixCCode]);
			else if(choice == printAns) OutputMatrix(matrix[matrixAnsCode]);
			else if(choice == det){
				ClearScreen();
				DrawString(2, 6, white, "Nhap ten ma tran can tinh: ");
				string name;
				cin >> name;
				cin.ignore();
				float n = CalcDeterminant(matrix[GetMatrix(name)]);
				if(n == -9999999){
					DrawString(2, 7, white, "Ma tran khong vuong");
				}
				else{
					DrawString(2, 7, white, "Det(" + name + ") = ");
					cout << n;
				}
			
			}
			else if(choice == inverse){
				ClearScreen();
				DrawString(2, 6, white, "Nhap ten ma tran can giai: ");
				string name;
				cin >> name;
				Matrix tmp = InverseMatrix(matrix[GetMatrix(name)]);
				if(tmp.column == -1){
					DrawString(2, 7, white, "Ma tran khong vuong");
				}
				else if(tmp.column == 0){
					DrawString(2, 7, white, "Ma tran khong kha nghich !!!");		
				}
				else{
					OutputMatrix(tmp);
				}
			}
			else if(choice == multiply){
				ClearScreen();
				DrawString(2, 6, white, "Nhap ten ma tran 1: ");
				string name1;
				cin >> name1;
				cin.ignore();
				DrawString(2, 7, white, "Nhap ten ma tran 2: ");
				string name2;
				cin >> name2;
				cin.ignore();
				matrix[matrixAnsCode] = MultiplyMatrix(matrix[GetMatrix(name1)], matrix[GetMatrix(name2)]);
				if(matrix[matrixAnsCode].column == -1){
					DrawString(2, 8, white, "Khong hop le");
				}
				else OutputMatrix(matrix[matrixAnsCode]);
			}
			else if(choice == rank){
				ClearScreen();
				DrawString(2, 6, white, "Nhap ten ma tran: ");
				string name;
				cin >> name;
				cin.ignore();
				DrawString(2, 7, white, "Rank = ");
				cout << Ranking(matrix[GetMatrix(name)]);
			}
			else if(choice == system){
				ClearScreen();
				DrawString(2, 6, white, "Nhap ten ma tran can giai: ");
				string name;
				cin >> name;
				SolveSystem(matrix[GetMatrix(name)]);
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

void MatrixMode::Render(){
	if(input == up || input == down){
		if(stage == inputMatrix){
			DrawString(2, prevChoice +  9, white, matrixName[prevChoice]);
			DrawString(2, choice + 9, red, matrixName[choice]);
		}
		else if(stage == doTask){
			DrawString(2, prevChoice +  9, white, task[prevChoice]);
			DrawString(2, choice + 9, red, task[choice]);
		}
	}
}
