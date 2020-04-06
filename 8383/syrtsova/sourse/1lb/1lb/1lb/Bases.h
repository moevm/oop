#pragma once
#include "factory.h"
#include "Object.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "Map.h"

class Bases : public Factory, public Object{
	enum allClasses
	{	magician = 1, healer, archer, arbalester, swordsman, spear };
	struct Coordinates {
		int x, y;
	}XY;
	string units[7] = {"test", "magician", "healer", "archer", "arbalester", "swordsman", "spear" };
	string army = "";
	int resources;
	int cost_arbalester = 1;
	int cost_archer = 2;
	int cost_swordsman = 1;
	int cost_spear = 2;
	int cost_healer = 2;
	int cost_magician = 3;
protected:
	char name;
	int ester;
	int health;
	bool shild = false;
	bool fleet = false;
public:
	int count_units = 0;
	int X, Y;
	Bases(char N, int health, int res);
	void production(int select, Map *field);
	void initialization(int resources);
	Swordsman* createSwordsman(Map *field) override;
	Spear* createSpear(Map *field) override;
	Magician* createMagician(Map *field) override;
	Healer* createHealer(Map *field) override;
	Archer* createArcher(Map *field) override;
	Arbalester* createArbalester(Map *field) override;
	

	void showAllUnits();
	void functional(Map* field);
	int selectUnit(Map* field);
	void showResour();
	void showState();
	int getEster();
	int getHealth();
	bool getShild();
	void activateShild();
	void equipment();
	struct List {
		int count_unit[3] = { 0 , 0 , 0};
		int count_warlock[3] = { 0 , 0 , 0};
		int count_archer[3] = { 0 , 0 , 0};
		int count_warrior[3] = { 0 , 0 , 0};
	}list;

	~Bases() {}
};

