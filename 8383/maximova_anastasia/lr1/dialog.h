#pragma once
#include "GameField.h"
#include "FirstGamer.h"

class Dialog {		//для взаимодействия с игроками и вызова методов
private:
	char answer;
	int exit;

public:

	Dialog();
	void caseStart();
	bool choice();
	void rules();
	void infoUnit();
	void casePlay();
};
