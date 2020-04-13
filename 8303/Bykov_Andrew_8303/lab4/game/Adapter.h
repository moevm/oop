#pragma once
#include <string>
#include "Logger.h"

class Base;
class Unit;
class Field;
class Adapter : public Logger {
public:
	bool writeAble;
	bool fileWriteAble;

	Adapter(bool writeAble = true, bool fileWriteAble = false);
	void switchLog(std::string mod);

	void createBase(Base *base);
	void createField(Field *field);

	void move_Player(string dir);
	void create_Player(string unit);
	void attack_Player(string target);
	void switch_Player();

	void create_Unit(Unit* unit);
	void move_Unit(string unit, string dir);
	void attack_Unit(string unit, string target);
	void dead_Unit(string unit);
	void attacked_Unit(string unit);
	void stamina_Unit(Unit * unit);
	void armor_Unit(Unit * unit);
	void attackRate_Unit(Unit * unit);
	void number_Unit(Unit * unit);
	void failAttack_Unit(Unit * unit);
	void failMove_Unit(Unit * unit);
	void interact_Unit(Unit * unit, string object);

	void createUnit_Base(Base * base);
	void failCreateUnit_Base(Base * base);
	void gold_Base(Base * base);
	void overlimit_Base(Base * base);
};