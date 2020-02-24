#pragma once
#include "Unit.h"

class EmptyUnit : public Unit {
public :
	EmptyUnit();
	bool update() { return false; };
};

class Infantry : public Unit {
public:

	Infantry();
};
class Berserks : public Infantry{
public:
	Berserks(int N);
	bool update();
};
class Spearmen : public Infantry {
public:
	Spearmen(int N);
	bool update();
};

class Archers : public Unit {
public:

	Archers();
};
class LongShooters : public Archers {
public:
	LongShooters(int N);
	bool update();
};
class Hunters : public Archers {
public:
	Hunters(int N);
	bool update();
};

class Cavalry : public Unit {
public:

	Cavalry();
}; 
class Ulans : public Cavalry {
public:
	Ulans(int N);
	bool update();
};
class Cuirassiers : public Cavalry {
public:
	Cuirassiers(int N);
	bool update();
};

class WaterBerserks : public Berserks
{
public:
	WaterBerserks(int N) : Berserks(N) { setTeam(0); };
};
class FireBerserks : public Berserks
{
public:
	FireBerserks(int N) : Berserks(N) { setTeam(1); };
};
class WaterSpearmen : public Spearmen
{
public:
	WaterSpearmen(int N) : Spearmen(N) { setTeam(0); };
};
class FireSpearmen : public Spearmen
{
public:
	FireSpearmen(int N) : Spearmen(N) { setTeam(1); };
};
class WaterLongShooters : public LongShooters
{
public:
	WaterLongShooters(int N) : LongShooters(N) { setTeam(0); };
};
class FireLongShooters : public LongShooters
{
public:
	FireLongShooters(int N) : LongShooters(N) { setTeam(1); };
};
class WaterHunters : public Hunters
{
public:
	WaterHunters(int N) : Hunters(N) { setTeam(0); };
};
class FireHunters : public Hunters
{
public:
	FireHunters(int N) : Hunters(N) { setTeam(1); };
};
class WaterUlans : public Ulans
{
public:
	WaterUlans(int N) : Ulans(N) { setTeam(0); };
};
class FireUlans : public Ulans
{
public:
	FireUlans(int N) : Ulans(N) { setTeam(1); };
};
class WaterCuirassiers : public Cuirassiers
{
public:
	WaterCuirassiers(int N) : Cuirassiers(N) { setTeam(0); };
};
class FireCuirassiers : public Cuirassiers
{
public:
	FireCuirassiers(int N) : Cuirassiers(N) { setTeam(1); };
};

class CompositeUnit 
{
private:
	const int maxSquadsNumber = 10;
	
public:
	int num = 0;
	Unit ** units;
	CompositeUnit();
	void addUnit(Unit* p);
	void delUnit(Unit * p);
	bool notify();
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
class Field;
class Base : public ArmyFactory
{
protected:
	CompositeUnit * army = new CompositeUnit;
	Point spawnSpot;
	Point baseSpot;
	Field * field;
	int health;
	bool spawnFree = true;
	const int maxArmyField = 20;
	const int maxUnitsNumber = 150;
	const int maxBerserksNumber = 100;
	const int maxSpearmenNumber = 80;
	const int maxHuntersNumber = 20;
	const int maxLongShootersNumber = 20;
	const int maxUlansNumber = 50;
	const int maxCuirassiersNumber = 10;
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
	Base(Point s, Point b, Field * f) : spawnSpot(s), baseSpot(b), field(f) {};
	string command;
public:
	
	void printInfo();
	bool setCommand(string c);
	string getCommand() const;
};
class WaterBase : public Base
{

public:
	WaterBase(Point s, Point b, Field * f);

	bool createBerserks(int N);
	bool createSpearmen(int N);
	bool createLongShooters(int N);
	bool createHunters(int N);
	bool createUlans(int N);
	bool createCuirassiers(int N);
};
class FireBase : public Base
{

public:
	FireBase(Point s, Point b, Field * f);

	bool createBerserks(int N);
	bool createSpearmen(int N);
	bool createLongShooters(int N);
	bool createHunters(int N);
	bool createUlans(int N);
	bool createCuirassiers(int N);
};



