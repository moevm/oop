#pragma once
#include "Flyweight.h"

class Unit {

private:

	int x, y;
	char id, type;
	Atributes *characteristics;

public:

	Unit();
	void attack(Unit* a);
	void get_hit(int damage);
	void check_armor(Unit* a);
	void setName(char a);
	void setType(char a);
	void setCoordinats(int x_, int y_);
	char getid();
	char getType();
	int getx();
	int gety();
	Atributes* getCharactresistics();
	void changeCharactresistics(Atributes* a);
	~Unit();

};

class Warrior : public Unit {

public:

	Warrior();
	~Warrior();

};

class Swordman : public Warrior {

public:

	Swordman();
	~Swordman();
};

class Spearman : public Warrior {

public:

	Spearman();
	~Spearman();

};

class Archer : public Unit {

public:

	Archer();
	~Archer();
};

class Slinger : public Archer {

public:

	Slinger();
	~Slinger();

};

class Bowman : public Archer {

public:

	Bowman();
	~Bowman();
};

class Cavalry : public Unit {

public:

	Cavalry();
	~Cavalry();

};

class LightCavalry : public Cavalry {

public:

	LightCavalry();
	~LightCavalry();


};

class HeavyCavalry : public Cavalry {

public:

	HeavyCavalry();
	~HeavyCavalry();

};
