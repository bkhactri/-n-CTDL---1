#include "Draw.h"

void GotoXY(int x, int y){
	HANDLE hStdout;
	COORD destCoord;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	destCoord.X = x;
	destCoord.Y = y;
	SetConsoleCursorPosition(hStdout, destCoord);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = TRUE;
	SetConsoleTextAttribute(hStdout, 15);
	SetConsoleCursorInfo(hStdout, &info);
}

void DrawCharacter(int x, int y, int color, int character){
	char symbol = character;
	HANDLE hStdout;
	COORD destCoord;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	destCoord.X = x;
	destCoord.Y = y;
	SetConsoleCursorPosition(hStdout, destCoord);
	SetConsoleTextAttribute(hStdout, color);
	cout << symbol;
	// Draw symbol

	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleTextAttribute(hStdout, 15);
	SetConsoleCursorInfo(hStdout, &info);
	// Remove cursor 
}

void DrawString(int x, int y, int color, string longString){
	HANDLE hStdout;
	COORD destCoord;
	hStdout     = GetStdHandle(STD_OUTPUT_HANDLE);
	destCoord.X = x;
	destCoord.Y = y;
	SetConsoleCursorPosition(hStdout, destCoord);
	SetConsoleTextAttribute(hStdout, color);
	cout << longString;
	// Draw symbol

	CONSOLE_CURSOR_INFO info;
	info.dwSize   = 100;
	info.bVisible = FALSE;
	SetConsoleTextAttribute(hStdout, 15);
	SetConsoleCursorInfo(hStdout, &info);
	// Remove cursor 
}
