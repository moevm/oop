#include "pch.h"
#include "Attribute.h"
#include <iostream>

Health::Health() {}
Health::Health(int h) : _health(h) {}
int Health::returnHealth(){
	return _health;
}

void Health::change(int shift)
{
	if(shift > 0)
	if (_health == _max_health)
		return;
	_health += shift;
	if (_health <= 0)
		delete this;
}

void Health::setAtrib(int h)
{
	_health = h;
	_max_health = _health;
}

Health::~Health()
{
	std::cout << std::endl << "Критический урон!";
}


Armor::Armor() {}
Armor::Armor(int a) : _armor (a) {}
int Armor::returnArmor(){
	return _armor;
}
void Armor::setAtrib(int a)
{
	_armor = a;
}

void Armor::change(int shift)
{
	_armor += shift;
	if (_armor <= 0)
		_armor = 0;
}


Armor::~Armor() {}

Attack::Attack() {}
Attack::Attack(int a) : _attack(a) {}
int Attack::returnAttack(){
	return _attack;
}
void Attack::setAtrib(int a)
{
	_attack = a;
}
void Attack::change(int shift)
{
	_attack += shift;
	if (_attack <= 0)
		_attack = 0;
}
Attack::~Attack() {}

Radius::Radius() {}
Radius::Radius(int r) : _radius(r) {}
int Radius::returnRadius(){
	return _radius;
}
void Radius::setAtrib(int r)
{
	 _radius = r;
	 _radius_max = _radius;
}

void Radius::change(int shift)
{
	_radius += shift;

}


int Radius::getRadius()
{
	return _radius;
}

void Radius::refresh()
{
	_radius = _radius_max;
}

Radius::~Radius() {}


Name::Name() {}
Name::Name(char n) : _name(n) {}
char Name::returnName() {
	return _name;
}
void Name::setAtrib(int n)
{
	_name = n;
}
Name::~Name() {}


void SpecialResources::setAtrib(int &sp)
{
	if (_special_1 == 0)
	{
		_special_1 = sp;
	}
	else
		_special_2 = sp;
}

void SpecialResources::changeSp1(int sp)
{
	_special_1 = sp;
}

void SpecialResources::changeSp2(int sp)
{
	_special_2 = sp;
}

int SpecialResources::returnSp1()
{
	return _special_1;
}

int SpecialResources::returnSp2()
{
	return _special_2;
}