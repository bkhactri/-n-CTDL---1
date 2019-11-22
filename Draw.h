#pragma once
#include<windows.h>
#include<iostream>
using namespace std;

#define green 10
#define red 12
#define yellow 14
#define white 15
#define header  16
#define blank 32
#define border 219

void DrawCharacter(int x, int y, int color, int character);
void DrawString(int x, int y, int color, string longString);
void GotoXY(int x, int y);
