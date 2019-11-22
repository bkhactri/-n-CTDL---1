#include<iostream>
#include<math.h>
#include<iomanip>
#include "Draw.h"
#include <limits>
#include <conio.h>
using namespace std;

struct Vector
{
	int count;
	float* vector;
};

int GetVector(string name);
void InputVector(Vector& input);
void OutputVector(Vector input);
void DeleteVector(Vector input);
Vector PlusTwoVector(Vector in1, Vector in2);
Vector MultiplyVectorWithNumber(Vector in, float number);
