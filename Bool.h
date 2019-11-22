#include<string>
#include "Draw.h"
#include <conio.h>
#include <math.h>
#include<string>
#include<sstream>
using namespace std;

struct Bool{ 
	int matrix[6][6];
	bool full;
	bool null;
	stringstream result[10];
	int ansCount;
	int set[10][10];	
	
	
	Bool();
	~Bool();
	
	void CreateSet(int multiply[], bool multiplyFlag[], int& count);
	void Delete(int multiply[], bool multiplyFlag[], int count);
	void Extract(int extracted[], int &extractedCount, int multiply[], bool multiplyFlag[], int count);
	void Fill(int extracted[], int extractedCount, int pos, int filledCount, int shortestResult[], int &minCell);
	bool Compare(int tmp[6][6]);
	void Convert(int minCell);
	void Simplify();
	
	void InputKarnaugh();
	void OutputKarnaugh();
	void OutputResult();
};
