#include "pch.h"
#include "Bases.h"
#include "ctime"
#include "Map.h"
#include <iostream>

enum allClasses
{
	magician = 1,
	healer, 
	archer, 
	arbalester, 
	swordsman, 
	spear
};


Bases::Bases(char N, int health, int res) : name(N), health(health), resources(res) 
{ 
	object = name;
	X = 1;
	Y = 1;
	initialization(res);
	XY.x = X + 1;
	XY.y = Y + 1;
}

int rand(int &res)
{
	srand(time(0));
	int pers = int(res*0.1) + rand() % int(res - res*0.1);
	res -= pers;
	return pers;
}

void Bases::initialization(int resources)
{
	int res = resources;
	list.count_warrior[0] = rand(res);
	list.count_archer[0] = rand(res);
	list.count_warlock[0] = rand(res);
}

Swordsman* Bases::createSwordsman(Map *field) {
	Swordsman *sword = new Swordsman(XY.x, XY.y);
	(*field).add_on_map(XY.x, XY.y, sword);
	system("cls");
	(*field).print_map();
	sword->movie(field);
	return sword;
}
Spear* Bases::createSpear(Map *field) {
	Spear *sp = new Spear(XY.x, XY.y);
	(*field).add_on_map(XY.x, XY.y, sp);
	system("cls");
	(*field).print_map();
	sp->movie(field);
	return sp;
}
Magician* Bases::createMagician(Map *field) {
	Magician *mag = new Magician(XY.x, XY.y);
	(*field).add_on_map(XY.x, XY.y, mag);
	system("cls");
	(*field).print_map();
	mag->movie(field);
	return mag;
}
Healer* Bases::createHealer(Map *field) {
	Healer *heal = new Healer(XY.x, XY.y);
	(*field).add_on_map(XY.x, XY.y, heal);
	system("cls");
	(*field).print_map();
	heal->movie(field);
	return heal;
}
Archer* Bases::createArcher(Map *field) {
	Archer *arh = new Archer(XY.x, XY.y);
	(*field).add_on_map(XY.x, XY.y, arh);
	system("cls");
	(*field).print_map();
	arh->movie(field);
	return arh;
}
Arbalester* Bases::createArbalester(Map *field) {
	Arbalester *arb = new Arbalester(XY.x, XY.y);
	(*field).add_on_map(XY.x, XY.y, arb);
	system("cls");
	(*field).print_map();
	arb->movie(field);
	return arb;
}

void Bases::production(int selsect, Map *field)
{
	if (!(*field).isUnit(XY.x,XY.y))
	switch(selsect)
	{
	case  allClasses::arbalester:
		{
		if (cost_arbalester <= list.count_archer[0]) {
			list.count_archer[0] -= cost_arbalester;
			list.count_archer[1]++;
			list.count_unit[0]++;
			//создание арбалетчика
			createArbalester(field);
		}
		}
	case allClasses::archer:
	{
		if (cost_archer <= list.count_archer[0]) {
			list.count_archer[0] -= cost_archer;
			list.count_archer[2] ++;
			list.count_unit[0]++;
			//создание лучника
			createArcher(field);
		}
	}
	case allClasses::swordsman:
	{
		if (cost_swordsman <= list.count_warrior[0]) {
			list.count_warlock[0] -= cost_swordsman;
			list.count_warlock[1] ++;
			list.count_unit[1]++;
			//создание мечника
			createSwordsman(field);
		}
	}
	case allClasses::spear:
	{
		if (cost_spear <= list.count_warrior[0]) {
			list.count_warrior[0] -= cost_spear;
			list.count_warrior[2] ++;
			list.count_unit[1]++;
			//создание рыцаря
			createSpear(field);
		}
	}
	case allClasses::healer:
	{
		if (cost_healer <= list.count_warlock[0]) {
			list.count_warlock[0] -= cost_healer;
			list.count_warlock[1] ++;
			list.count_unit[2]++;
			//создание хиллера
			createHealer(field);
		}
	}
	case allClasses::magician:
	{
		if (cost_magician <= list.count_warlock[0]) {
			list.count_warlock[0] -= cost_magician;
			list.count_warlock[2] ++;
			list.count_unit[2]++;
			//создание мага
			createMagician(field);
		}
	}
	default:
		break;
	}
}



