#pragma once
#include "Object.h"
#include <limits>
#include <iostream>
#include "Map.h"


class Units : public Object
{
public:
	struct Coordinates {
		int x, y;
	}XY;
	Units(char N,const int &h,const int &ar,const int &at,const int &r);
	bool movie(Map *field);
	void selected(Map *field);
	bool rules(Map *field, int x, int y);
	~Units();
protected:
	char name;
	int health;
	int armor;
	int attack;
	int radius;
};

