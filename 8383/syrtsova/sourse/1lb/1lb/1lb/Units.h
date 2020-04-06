#pragma once
#include "Object.h"
#include <limits>
#include <iostream>
#include "Map.h"
#include "Attribute.h"


class Units : public Object
{
public:
	Name name;
	Health health;
	Armor armor;
	Attack attack;
	Radius radius;
	Units *link;
	virtual void showSkills() = 0;
	virtual void selectSkill(int ch, Map* field) = 0;
	struct Coordinates {
		int x, y;
	}XY;
	struct Line {
		int x, y;
	}_xy;
	Units* getLink(Map* field);
	void managment(Map *field);
	void selectLine();
	void useSkill(Map *field);
	Units(char N,const int &h,const int &ar,const int &at,const int &r);
	void movie(Map *field);
	void selected(Map *field);
	void printStats();
	bool rules(Map *field, int x, int y);
	~Units();
protected:
	void operator + (Units* unit);
};

