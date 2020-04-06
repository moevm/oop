#pragma once

class Health
{
	int health;
	int max_health;
public:
	Health();
	void change(int shift);
	void setAtrib(int h);
	Health(int h);
	int returnHealth();
	~Health();
};


class Armor
{
	int armor;
public:
	Armor();
	void setAtrib(int a);
	void change(int shift);
	Armor(int a);
	int returnArmor();
	~Armor();
};

class Attack
{
	int attack;
public:
	Attack();
	void setAtrib(int a);
	void change(int shift);
	Attack(int a);
	int returnAttack();
	~Attack();
};


class Radius {
	int radius;
public:
	Radius();
	void setAtrib(int rh);
	void change(int shift);
	Radius(int r);
	int returnRadius();
	~Radius();
};

class Name {
	char name;
public:
	Name();
	void setAtrib(int n);
	void change(int shift);
	Name(char n);
	char returnName();
	~Name();
};