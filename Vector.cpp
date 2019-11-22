#include "Vector.h"

/*VECTOR SOVLE*/

int GetVector(string name){
	if(name == "A" || name == "a") return 1;
	else if(name == "B" || name == "b") return 2;
	else if(name == "C" || name == "c") return 3;
	else if(name == "Ans" || name == "ans") return 4;
	return 0;
}

void InputVector(Vector& input)
{
	for(int i = 2; i < 49; i++){
		for(int j = 6; j < 29; j++){
			DrawCharacter(i, j, white, blank);
		}
	}
	
	DrawString(2, 6, white, "Nhap vao so thanh phan cua vector: ");
	cin >> input.count;
	cin.ignore();
	input.vector = new float[input.count];
	for (int i = 0; i < input.count; i++){
		DrawString(2, i + 8, white, "x");
		cout << i+1 << ": "; 
		GotoXY(7, i+8);
		cin >> input.vector[i];
	}
	getch();
	fflush(stdin);
	GetAsyncKeyState(VK_RETURN);
}

void OutputVector(Vector input)
{
	for(int i = 2; i < 49; i++){
		for(int j = 6; j < 29; j++){
			DrawCharacter(i, j, white, blank);
		}
	}
		
	if(input.count <= 0) DrawString(2, 6, white, "Null vector");
	else{	
		GotoXY(2, 6);
		cout << "(";
		for (int i = 0; i < input.count; i++){
			if (i == input.count - 1){
				cout << input.vector[i];
			}
			else cout << input.vector[i] << ", ";
	
		}
		cout << ")";
	}
}

void DeleteVector(Vector input)
{
	delete input.vector;
}

Vector PlusTwoVector(Vector in1, Vector in2)
{
	Vector sum;
	sum.count = in1.count;
	if (in1.count != in2.count){
		sum.count=-1;
		return sum;
	}
	else{
		sum.vector = new float[sum.count];
		for (int i = 0; i < sum.count; i++){
			sum.vector[i] = in1.vector[i] + in2.vector[i];
		}
	}
	return sum;
}

Vector MultiplyVectorWithNumber(Vector in, float number)
{
	Vector result;
	result.count = in.count;
	result.vector = new float[result.count];
	for (int i = 0; i < result.count; i++){
		result.vector[i] =number*in.vector[i];
	}
	return result;
}
