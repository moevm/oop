#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "Atributes.h"
//#include "Field.h"
using namespace std;

class Unit : public Physical, public Weapon, public Spirit
{
public:
	int number;
	int max_number;
	int X; int Y;

	string army;
	string s_class;
	string num;
	string code;

	Unit();
	//virtual void place(Field &field);
	void option(std::string NAME, string SUB_NAME, int ARMOR, int ATTACK, int NUMBER = 0);
	void change_num(int new_num);
	void set_cords(int X, int Y);
	void set_team(int t);
};

