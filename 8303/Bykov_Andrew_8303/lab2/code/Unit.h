#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

struct Point
{
	int x;
	int y;
	Point(int X, int Y) : x(X), y(Y) {};
	Point() :x(0), y(0) {};

	bool operator!=(Point &other) {
		return x != other.x || y != other.y;
	}
	bool operator!=(Point other) {
		return x != other.x || y != other.y;
	}
	bool operator==(Point other) {
		return x == other.x && y == other.y;
	}

};

using namespace std;
class Base; class Field;
class Unit
{
protected:
	Point place;
	
	const int max_number = 99;
	int number;
	
	class Properties	
	{
	public:
		Base * base;
		Field * field;
		int team;
		int serialNumber;
		bool enableAttack =  true;
		float debuffStamina = 1;
		float debuffAttack  = 1;
		float debuffArmor = 1;
	}properties;

	string army;
	string s_class;
	string num;

	void setTeam(int t);

public:
	void setCords(Point p);
	void setNumber(int new_num);
	void setSerialNumber(int num);
	void setBase(Base * base);
	void setField(Field * field);
	void enableAttack(bool t);
	void debuffStamina(float t);
	void debuffAttack(float t);
	void debuffArmor(float t);
	void clearUnit();

	Point getCords() const;
	int getHealth() const;
	int getAttack() const;
	int getArmor() const;
	int getRange() const;
	int getStamina() const;
	int getTeam() const;
	int getNumber() const;
	int getSerialNumber() const;
	string getSubclass() const;
	string getClass() const;
	string getSnum() const;
	bool isEmpty() const;
	bool attack(int x, int y);
	bool go(string dir);

	virtual bool update() = 0;
};

class FlyWeight
{
public:
	string name;
	int health;
	int stamina;
	int attack;
	int armor;
	int range;

	FlyWeight(string Name);
	string getName() { return name; }

};

class FlyweightFactory
{
private:
	static int num;
	static FlyWeight * flyweights[6];

public:
	static FlyWeight * getFlyWeight(string name);
	//static void reportTheFlyWeight();
};