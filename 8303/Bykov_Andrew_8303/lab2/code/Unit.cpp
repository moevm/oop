#include "Unit.h"
#include "Field.h"
#include <sstream>

void Unit::setSerialNumber(int num)
{
	properties.serialNumber = num;
}
void Unit::setNumber(int new_num)
{
	if (new_num > max_number)
	{
		cout << "Over limit\n";
		return;
	}
	if (new_num <= 0) clearUnit(); 
	else number = new_num;
	num = to_string(number);
	if (number < 10)
		num += " ";
	if (number == 0)
		num = "  ";
}
void Unit::setTeam(int t)
{
	properties.team = t;
}
void Unit::setBase(Base * base)
{
	properties.base = base;
}
void Unit::setField(Field * field)
{
	properties.field = field;
}
void Unit::setCords(Point p)
{
	place = p;
}
void Unit::clearUnit()
{
	number = 0;
	army = "  ";
	s_class = "  ";
}
void Unit::enableAttack(bool t)
{
	properties.enableAttack = t;
}

int Unit::getTeam() const
{
	return properties.team;
}
Point Unit::getCords() const 
{
	return place;
}
int Unit::getNumber() const
{
	return number;
}
int Unit::getSerialNumber() const
{
	return properties.serialNumber;
}
int Unit::getHealth() const
{
	return (FlyweightFactory::getFlyWeight(s_class)->health);
}
int Unit::getAttack() const
{
	return (FlyweightFactory::getFlyWeight(s_class)->attack);
}
int Unit::getArmor() const
{
	return (FlyweightFactory::getFlyWeight(s_class)->armor);
}
int Unit::getRange() const
{
	return (FlyweightFactory::getFlyWeight(s_class)->range);
}
int Unit::getStamina() const
{
	return (FlyweightFactory::getFlyWeight(s_class)->stamina);
}
string Unit::getSubclass() const
{
	return s_class;
}
string Unit::getClass() const
{
	return army;
}
string Unit::getSnum() const
{
	return num;
}
bool Unit::isEmpty() const
{
	return(getClass() == "  ");
}

void Unit::debuffStamina(float t)
{
	properties.debuffStamina = t;
}
void Unit::debuffAttack(float t)
{
	properties.debuffAttack = t;
}
void Unit::debuffArmor(float t)
{
	properties.debuffArmor = t;
}

bool Unit::attack(int x, int y)
{
	int distance = int(sqrt((place.x - x) * (place.x - x) + (place.y - y) * (place.y - y)));
	if (getRange() < distance)
	{
		cout <<"Unit " << properties.serialNumber << ": Target is not in range\n";
		return false;
	}
	Unit * enemy = properties.field->getUnit(x, y);
	int n = enemy->getNumber();
	enemy->setNumber(int((enemy->getHealth() * n - getAttack() * properties.debuffAttack * number) / enemy->getHealth()));
	return true;
}
bool Unit::go(string dir)
{
	if (dir == "left")
		if (properties.field->move_unit(place.x, place.y, place.x - 1, place.y))
		{
			place.x--;	return true;
		}
	if (dir == "right")
		if (properties.field->move_unit(place.x, place.y, place.x + 1, place.y))
		{
			place.x++; return true;
		}
	if (dir == "up")
		if (properties.field->move_unit(place.x, place.y, place.x, place.y - 1))
		{
			place.y--; return true;
		}
	if (dir == "down")
		if (properties.field->move_unit(place.x, place.y, place.x, place.y + 1))
		{
			place.y++; return true;
		}
	cout << "Unit " << properties.serialNumber << ": I can't go there\n";
	return false;
}

FlyWeight::FlyWeight(string Name) : name(Name)
{
	if (name == "Berserks")
	{
		health = 100;
		stamina = 8;
		attack = 150;
		armor = 50;
		range = 1;
	}
	if (name == "Spearmen")
	{
		health = 100;
		stamina = 6;
		attack = 100;
		armor = 100;
		range = 2;
	}
	if (name == "Hunters")
	{
		health = 50;
		stamina = 4;
		attack = 200;
		armor = 20;
		range = 6;
	}
	if (name == "LongShooters")
	{
		health = 50;
		stamina = 2;
		attack = 100;
		armor = 60;
		range = 10;
	}
	if (name == "Ulans")
	{
		health = 150;
		stamina = 10;
		attack = 100;
		armor = 100;
		range = 1;
	}
	if (name == "Cuirassiers")
	{
		health = 150;
		stamina = 8;
		attack = 150;
		armor = 200;
		range = 1;
	}
	if (name == "  ")
	{
		health = 0;
		stamina = 0;
		attack = 0;
		armor = 0;
		range = 0;
	}
}
int FlyweightFactory::num = 0;
FlyWeight * FlyweightFactory::flyweights[];
FlyWeight * FlyweightFactory::getFlyWeight(string name)
{
	for (int i = 0; i < num; i++)
		if (name == flyweights[i]->getName())
			return flyweights[i];
	flyweights[num] = new FlyWeight(name);
	return flyweights[num++];
}