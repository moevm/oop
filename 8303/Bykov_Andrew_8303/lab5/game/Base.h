#pragma once
#include "Unit.h"

class Field;
class Subject;

using namespace std;
class Base;
class Adapter;
class Command
{
public:
	virtual bool execute() = 0;
};
class MoveCommand : public Command
{
private:
	Base * base;
	string unit;
	string direction;
public:
	enum dirs
	{
		Left,
		Right,
		Up,
		Down
	};
	bool execute();
	MoveCommand(Base * Base, string who, dirs dir) : base(Base), unit(who)
	{
		if (dir == Left)
			direction = "left";
		if (dir == Right)
			direction = "right";
		if (dir == Up)
			direction = "up";
		if (dir == Down)
			direction = "down";

	};
};
class AttackCommand : public Command
{
private:
	Base * base;
	string unit;
	string x;
	string y;
public:
	AttackCommand(Base * Base, string who, string X, string Y) : base(Base), unit(who), x(X), y(Y) { };
	bool execute();
};
class CreateCommand : public Command
{
private:
	Base * base;
	string unit;
	string number;
public:
	CreateCommand(Base * Base, string who, string num) : base(Base), unit(who), number(num) { };
	bool execute();
};

class CompositeUnit : public Component
{
public:
	vector <Component*> units;
	CompositeUnit(Component *n = 0) : Component(n) {};
	void setLast(Component *n = 0) { Component::setNext(n); };
	void addUnit(Unit* p);
	void delUnit(Unit * p);
	bool volunteer();
};
class ArmyFactory
{
public:
	virtual bool createBerserks(int N) = 0;
	virtual bool createSpearmen(int N) = 0;
	virtual bool createLongShooters(int N) = 0;
	virtual bool createHunters(int N) = 0;
	virtual bool createUlans(int N) = 0;
	virtual bool createCuirassiers(int N) = 0;
};
class Base : public ArmyFactory, public Observer
{
	friend class Snapshot;
protected:
	CompositeUnit * army = new CompositeUnit;
	Point spawnSpot;
	Point baseSpot;
	Field * field;
	Adapter * adapter;
	Component * lastUnit = 0;
	string team;
	int health;
	int gold;
	bool spawnFree = true;
	const int maxSquadsNumber = 20;
	const int maxUnitsNumber = 150;
	const int maxBerserksNumber = 100;
	const int maxSpearmenNumber = 80;
	const int maxHuntersNumber = 20;
	const int maxLongShootersNumber = 20;
	const int maxUlansNumber = 50;
	const int maxCuirassiersNumber = 10;
	int SquadsNumber;
	int UnitsNumber;
	int BerserksNumber;
	int SpearmenNumber;
	int HuntersNumber;
	int LongShootersNumber;
	int UlansNumber;
	int CuirassiersNumber;

	bool doCommand();
	void update();
	bool place(Unit * unit);
	Base(Point s, Point b, Field * f, Adapter * a) : baseSpot(s), spawnSpot(b), field(f), adapter(a) {};
	string command;
	void setHealth(int h) { health = h; }
	void setGold(int g) { gold = g; }
public:
	
	
	void printInfo();
	void addGold(int money);
	bool setCommand(string c);
	bool order(Command * command);
	string getCommand() const;
	int getHealth() const;
	int getGold() const;
	string getTeam() const;
	void update(Subject * subject);
	void removeUnit(Unit* unit);
	Point getCords() const;
};
class WaterBase : public Base
{
private:
	bool createBerserks(int N);
	bool createSpearmen(int N);
	bool createLongShooters(int N);
	bool createHunters(int N);
	bool createUlans(int N);
	bool createCuirassiers(int N);
public:
	WaterBase(Point s, Point b, Field * f, Adapter * a);
};
class FireBase : public Base
{
private:
	bool createBerserks(int N);
	bool createSpearmen(int N);
	bool createLongShooters(int N);
	bool createHunters(int N);
	bool createUlans(int N);
	bool createCuirassiers(int N);
public:
	FireBase(Point s, Point b, Field * f, Adapter * a);
};
