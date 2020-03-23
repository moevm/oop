#pragma once
#include <iostream>
#include <string>
#include "GameField.h"

using namespace std;

class FirstGamer {// далее будет добавлен класс для второго игрока - пока демонстрационый вариант 
protected:
	string name;
	char team;
	int width;
	int height;
	int exit;
	char answer;
	int x, y;
	GameField* field;
public:
	FirstGamer();
	void caseName();
	bool choice2();
	void caseField();
	void addPeople();
	void caseAddCommand();
	bool caseError(int command);
	void caseDeleteUnit();
	bool caseError();
	void caseMovUnit();
	bool caseError(char a, int steps);
	void saveField();
	string getName();
	char getTeam();
};
