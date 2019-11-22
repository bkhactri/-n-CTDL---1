#include<iostream>
#include<math.h>
#include<iomanip>
#include "Draw.h"
#include <limits>
#include <conio.h>
using namespace std;

struct Matrix 
{
	int column;
	int row;
	float** mtx;
};

/*MATRIX*/
//Cai dat co ban
int GetMatrix(string name);
void InputMatrix(Matrix &input);//Nhap ma tran
void OutputMatrix(Matrix input);//Xuat
Matrix SaveData(Matrix input);//Luu tru du lieu ma tran
void DeleteMatrix(Matrix input);//Xoa cap phat
//Nhan ma tran
Matrix MultiplyMatrix(Matrix in1, Matrix in2);
//Tinh dinh thuc
float CalcDeterminant(Matrix in);
//Nghich dao ma tran
Matrix InverseMatrix(Matrix in);//Ham nghich dao chinh
Matrix AlgebraicComplement(Matrix in, int c, int r);//Ham tim phan bu c(i,j)
void Transposition(Matrix in);//Ham chuyen vi ma tran
//Hang ma tran
void BareissMatrix(Matrix in, float& sign);//Ham thuat toan Montante(Bareiss)
int Ranking(Matrix in);//Ham tim hang ma tran
//Giai he phuong trinh tuyen tinh
void SolveSystem(Matrix in);//Ham giai phuong trinh
void OutputSystem(Matrix in);//Ham xuat nghiem duy nhat
void OutputGenerality(Matrix in, int count);//Ham xuat nghiem tong quat
/*Bareiss la thuat toan kha phuc tap nen bon em se giai thich trong bao cao */
