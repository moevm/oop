#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;
class Unit;

class Mediator
{
public:
	virtual bool interact(Unit * unit) = 0;
};
class AttackMediator : public Mediator
{
protected:
	Unit * unit1;
	Unit * unit2;
public:
	AttackMediator(Unit * u1, Unit * u2);

	bool interact(Unit * unit);
};


class Base; 
class Field;
class Netral;
class Land;
class Subject;
class Adapter;
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

class Object
{
public:
	virtual void interact(Unit *) = 0;
};
class Component
{
	Component *next;
public:
	Component(Component *n)
	{
		next = n;
	}
	void setNext(Component *n)
	{
		next = n;
	}
	virtual bool volunteer()
	{
		if(next)
			return(next->volunteer());
		else return false;
	}
	virtual string getSubclass() { return 0; }
	virtual int getNumber() { return 0; }
	virtual Point getCords() { return Point(0, 0); }
	virtual bool update() { return 0; }
};
class Observer {
public:
	virtual void update(Subject* subject) = 0;
};
class Subject
{
public:
	std::vector<Observer*> observers;
	void addObs(Observer* observer);
	void delObs(Observer* observer);
	void notify();
};
class Unit : public Subject, public Component//, public Object
{
protected:
	Adapter * adapter;
	Point place;
	Field * field;
	Base * base;
	const int max_number = 99;
	
	class Properties	
	{
	public:
		int number;
		int team;
		int serialNumber = 0;
		bool enableAttack =  true;

		float debuffStamina = 1;
		float debuffAttack  = 1;
		float debuffArmor = 1;
	}properties;
	
	string army;
	string s_class;
	string num;

	void setTeam(int t);
	bool go(string dir);
	void clearUnit();

public:
	Mediator* mediator = nullptr;
	Unit(Component *n = 0) : Component(n) {};
	int isAttacked = 0;
	int isAttack = 0;

	bool attack(int x, int y);

	void setCords(Point p);
	void setSerialNumber(int num);
	void setNumber(int new_num);
	void setBase(Base * base);
	void setField(Field * field);
	void setAdapter(Adapter * adapter);

	void enableAttack(bool t);
	void debuffStamina(float t);
	void debuffAttack(float t);
	void debuffArmor(float t);
	
	Point getCords();
	string getSubclass();
	int getNumber();
	sf::Sprite getSprite(float frame);
	int getHealth() const;
	int getAttack() const;
	int getArmor() const;
	int getRange() const;
	int getStamina() const;
	int getTeam() const;
	int getSerialNumber() const;
	string getClass() const;
	string getSnum() const;
	bool isEmpty() const;
	Base * getBase() const;

	bool interact() { if (mediator) return(mediator->interact(this)); return false; }
};
class FlyWeight
{
public:
	sf::Texture tileSet;
	sf::Sprite sprite;
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
class TexturePack
{
public:
	sf::Texture tileSet;
	sf::Sprite sprite;
	string name;
	int team;
	int frame;
	TexturePack(string Name, int team, int frame);
	string getName() { return name; }
	int getTeam() { return team; }
	int getFrame() { return frame; }
};
class TextureFactory
{
private:
	static int num;
	static TexturePack * textures[100];

public:
	static TexturePack * getTexture(Unit * unit, float frame);
	static TexturePack * getTexture(Netral * netral);
	static TexturePack * getTexture(Land * land);
};
