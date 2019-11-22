#include "Bool.h"

Bool::Bool(){		
	full = true;
	null = true;
	ansCount = 0;
}

Bool::~Bool(){
	
}

void Bool::CreateSet(int multiply[], bool multiplyFlag[], int& count){
	// khoi tao gia tri so nguyen to cho cac bien x, y, z, t, -x, -y, -z, -t
	matrix[0][1] = 2;
	matrix[0][2] = 2;
	matrix[0][3] = 3;
	matrix[0][4] = 3;	
	matrix[5][1] = 7;
	matrix[5][2] = 5;
	matrix[5][3] = 5;
	matrix[5][4] = 7;
	matrix[1][0] = 11;
	matrix[2][0] = 11;
	matrix[3][0] = 13;
	matrix[4][0] = 13;	
	matrix[1][5] = 19;
	matrix[2][5] = 17;
	matrix[3][5] = 17;
	matrix[4][5] = 19;
	
	// tao to hop phep nhan so nguyen to trong tung o = v1^a * v2^b * v3^c * v4*d
	for(int i = 1; i <= 4; i++){
		for(int j = 1; j <= 4; j++){
			int v1 =  matrix[0][j]; // top
			int v2 = matrix[5][j]; // down
			int v3 = matrix[i][0]; // left
			int v4 = matrix[i][5]; // right
			for(int a = 0; a < 2; a++){
				for(int b = 0; b < 2; b++){
					for(int c = 0; c < 2; c++){
						for(int d = 0; d < 2; d++){
							int tmp = int(pow((double)v1, a))*int(pow((double)v2, b))*int(pow((double)v3, c))*int(pow((double)v4, d));
							bool flag = true;
							for(int k = 0; k < count; k++){
								if(multiply[k] == tmp){
									flag = false;
									break;
								}
							}
							if(flag == true){
								multiply[count] = tmp;
								multiplyFlag[count] = 1;
								count++; 
							}
						}
					}
				}
			}
		}
	}
	
	// Sap xep lai mang to hop phep nhan so nguyen to
	for(int i = 0; i < count - 1; i++){
		for(int j = i + 1; j < count; j++){
			if(multiply[i] > multiply[j]){
				int tmp = multiply[i];
				multiply[i] = multiply[j];
				multiply[j] = tmp;
			}
		}
	}
}

void Bool::Delete(int multiply[], bool multiplyFlag[], int count){ // xoa di nhung te bao khong ton tai trong Karnaugh
	for(int i = 1; i <= 4; i++){
		for(int j = 1; j <= 4; j++){
			if(matrix[i][j] == 0){
				int n = matrix[0][j]*matrix[5][j]*matrix[i][0]*matrix[i][5]; 
				for(int k = 0; k < count; k++){
					if(n < multiply[k]) break;
					if(n % multiply[k] == 0){
						multiplyFlag[k] = 0; // Xoa nhung phan tu la phan tu con 
					}
				}
			}
		}
	}
}

void Bool::Extract(int extracted[], int &extractedCount, int multiply[], bool multiplyFlag[], int count){ // Lay ra nhung phan tu gon nhat 
	for(int i = 0; i < count; i++){
		int flag = true;	
		if(multiplyFlag[i] == 0) flag = false;
		else{
			for(int j = 0; j < count; j++){
				if(multiply[j] >= multiply[i]) break;
				if(multiplyFlag[j] != 0 && multiply[i] % multiply[j] == 0){
	 				flag = false;
					break;
				}
			}
		}
		if(flag == true){
			extracted[extractedCount] = multiply[i];
			extractedCount++;
		}
	}
}

void Bool::Fill(int cell[], int cellCount, int pos, int filledCount, int shortestResult[], int &minCell){ // Phu nguoc lai Karnaugh rong de so sanh
	if(pos < cellCount ){
		Fill(cell, cellCount, pos + 1, filledCount, shortestResult, minCell);
		shortestResult[filledCount] = cell[pos];
		Fill(cell, cellCount, pos + 1, filledCount + 1, shortestResult, minCell);
	}
	else{
		int tmp[6][6];
		for(int i = 1; i <= 4; i++){
			for(int j = 1; j <= 4; j++){
				tmp[i][j] = 0;
				for(int k = 0; k < filledCount; k++){
					if(matrix[0][j]*matrix[5][j]*matrix[i][0]*matrix[i][5] % shortestResult[k] == 0){
						tmp[i][j] = 1;
					}
				}
			}
		}
		
		if(Compare(tmp) == true)
			if(filledCount < minCell){
				minCell = filledCount;
				ansCount = 1;
				for(int i = 0; i < minCell - 1; i++){
					for(int j = 0; j < minCell; j++){
						if(shortestResult[i] < shortestResult[j]){
							int k = shortestResult[i];
							shortestResult[i] = shortestResult[j];
							shortestResult[j] = k;
						}
					}
				}
				for(int i = 0; i < minCell; i++){
					set[0][i] = shortestResult[i];
				}
				
			}
			if(filledCount == minCell){
				bool flag = false;
				int tmpSet[10];
				for(int i = 0; i < minCell; i++){
					tmpSet[i] = shortestResult[i];
				}
				for(int i = 0; i < minCell - 1; i++){
					for(int j = 0; j < minCell; j++){
						if(shortestResult[i] < shortestResult[j]){
							int k = shortestResult[i];
							shortestResult[i] = shortestResult[j];
							shortestResult[j] = k;
						}
					}
				}
				for(int i = 0; i < minCell; i++){
					if(shortestResult[i] != set[ansCount-1][i]){
						flag = true;
						break;
					} 
				}
				if(flag == true){
					for(int i = 0; i < minCell; i++){
						set[ansCount][i] = shortestResult[i];
					}
					ansCount++;
				}
				for(int i = 0; i < minCell; i++){
					shortestResult[i] = tmpSet[i];
				}
			}
	}
}

bool Bool::Compare(int tmp[6][6]){// so sanh Karnaugh tmp voi Karnaugh da nhap
	for(int i = 1; i <= 4; i++){
		for(int j = 1; j <= 4; j++){
			if(tmp[i][j] != matrix[i][j]){
				return false;
			}
		}
	}
	return true;
}

void Bool::Convert(int minCell){// Tu so chuyen sang ki tu 
	for(int n = 0; n < ansCount; n++){
		bool first = false;
		for(int i = 0; i < minCell; i++){ 
			if(first == true) result[n] << " V ";
			if(set[n][i] % 2 == 0) result[n] << "x";
			else if(set[n][i] % 3 == 0) result[n] << "-x";
			if(set[n][i] % 5 == 0) result[n] << "y";
			else if(set[n][i] % 7 == 0) result[n] << "-y";
			if(set[n][i] % 11 == 0) result[n] << "z";
			else if(set[n][i] % 13 == 0) result[n] << "-z";
			if(set[n][i] % 17 == 0) result[n] << "t";
			else if(set[n][i] % 19 == 0) result[n] << "-t";
			first = true;
		}	
	}
}

void Bool::Simplify(){
	for(int i = 2; i < 49; i++){
		for(int j = 6; j < 29; j++){
			DrawCharacter(i, j, white, blank);
		}
	}
	
	GotoXY(2, 6);
	result[0].str(""); 
	if(full == true) result[0] << 1;
	else if(null == true) result[0] << 0;
	else{
		int multiply[81]; // Mang tich cua to hop so nguyen to
		bool multiplyFlag[81]; // Mang kiem tra ton tai cua te bao trong karnaugh
		int count = 0;
		
		int	extracted[10]; // Mang luu lai nhung te bao don gian nhat ton tai trong Karnaugh
		int extractedCount = 0;
		
		int minCell = 99 ;
		int shortestResult[10]; // Mang chua cong thuc don gian nhat
	
		CreateSet(multiply, multiplyFlag, count); // Tao mang to hop phep nhan so nguyen to tu tung o Karnaugh
		Delete(multiply, multiplyFlag, count); // Loai di nhung te bao khong ton tai trong Karnaugh
		Extract(extracted, extractedCount, multiply, multiplyFlag, count); // Lay ra nhung te bao co cong thuc gon nhat
	 	Fill(extracted, extractedCount, 0, 0, shortestResult, minCell); // Phu nguoc lai Karnaugh rong bang cach de quy de tim ra cong thuc ngan nhat
		Convert(minCell); // Chuyen gia tri thanh chuoi ki tu bool
	}
	

	for(int i = 0; i < ansCount; i++){
		GotoXY(2, i + 6);
		cout << result[i].str();
	}
	
	
	getch();
	fflush(stdin);
	GetAsyncKeyState(VK_RETURN);
}

void Bool::InputKarnaugh(){
	for(int i = 2; i < 49; i++){
		for(int j = 6; j < 29; j++){
			DrawCharacter(i, j, white, blank);
		}
	}
	
	DrawString(2, 6, white, "Nhap bieu do Karnaugh");
	
	DrawString(5, 8, white, "x x_x_x");
	DrawString(3, 10, white, "z");
	DrawString(3, 12, white, "z");
	DrawString(2, 14, white, "_z");
	DrawString(2, 16, white, "_z");
	DrawString(13, 10, white, "_t");
	DrawString(13, 12, white, "t");
	DrawString(13, 14, white, "t");
	DrawString(13, 16, white, "_t");
	DrawString(4, 18, white, "_y y y_y");
	
	for(int i = 1; i <= 4; i++){
		for(int j = 1; j <= 4; j++){
			GotoXY(j*2 + 3, i*2 + 8);
			cin >> matrix[i][j];
			if(matrix[i][j] == 0) full = false;
			else null = false; 
		}
	}
	
	getch();
	fflush(stdin);
	GetAsyncKeyState(VK_RETURN);
}

void Bool::OutputKarnaugh(){
	for(int i = 2; i < 49; i++){
		for(int j = 6; j < 29; j++){
			DrawCharacter(i, j, white, blank);
		}
	}
	
	DrawString(5, 8, white, "x x_x_x");
	DrawString(3, 10, white, "z");
	DrawString(3, 12, white, "z");
	DrawString(2, 14, white, "_z");
	DrawString(2, 16, white, "_z");
	DrawString(13, 10, white, "_t");
	DrawString(13, 12, white, "t");
	DrawString(13, 14, white, "t");
	DrawString(13, 16, white, "_t");
	DrawString(4, 18, white, "_y y y_y");
	
	for(int i = 1; i <= 4; i++){
		for(int j = 1; j <= 4; j++){
			GotoXY(j*2 + 3, i*2 + 8);
			cout << matrix[i][j];
		}
	}
	
	getch();
	fflush(stdin);
	GetAsyncKeyState(VK_RETURN);
}

void Bool::OutputResult(){
	for(int i = 2; i < 49; i++){
		for(int j = 6; j < 29; j++){
			DrawCharacter(i, j, white, blank);
		}
	}
	
	for(int i = 0; i < ansCount; i++){
		GotoXY(2, i + 6);
		cout << result[i].str();
	}
	
	getch();
	fflush(stdin);
	GetAsyncKeyState(VK_RETURN);
}














