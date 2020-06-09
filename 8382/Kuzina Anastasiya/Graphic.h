#pragma once
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "iostream"
#include "Field.h"
#include "Player.h"
#include <Synchapi.h>

enum consoleColor {
	black = 0,
	blue = 1,
	green = 2,
	cyan = 3,
	red = 4,
	magenta = 5,
	brown = 6,
	lightGray = 7,
	darkGray = 8,
	lightBlue = 9,
	lightGreen = 10,
	lightCyan = 11,
	lightRed = 12,
	lightMagenta = 13,
	yellow = 14,
	white = 15
};

class graphic {
	VOID WINAPI Sleep(DWORD dwMilliseconds);
	HANDLE hConsole;
public:
	graphic();
	void help();
	void setTextColor(int text = 15, int background = 0);
	void setTitle();
	void info(unit* camera_men);
	void camera(field& F, player* tmp, bool inf = true);

};