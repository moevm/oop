#include "Unit.h"



Unit::Unit()
{
	army = "  ";
	s_class = "  ";
	number = 0;
	team = 0;
	max_number = 99;
	num = "  ";
}
/*
void Unit::place(Field &field)
{
	return;
}
*/
void Unit :: option(std::string NAME, string SUB_NAME, int ARMOR, int ATTACK, int NUMBER)
{
	change_num(NUMBER);
	army = NAME;
	s_class = SUB_NAME;
	//health = HEALTH;
	armor = ARMOR;
	attack = ATTACK;
	code = string(1, army[0]) + string(1, s_class[0]);
}

void Unit::change_num(int new_num)
{
	if (new_num > max_number)
	{
		cout << "Over limit\n";
		return;
	}
	number = new_num;
	num = to_string(number);
	if (number < 10)
		num += " ";
}

void Unit::set_cords(int x, int y)
{
	X = x;
	Y = y;
}

void Unit::set_team(int t)
{
	team = t;
}