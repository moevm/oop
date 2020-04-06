#pragma once
#include "Object.h"
#include "Units.h"

class Neutral : public Object
{
	int x_max;
	int y_max;
protected:
	char name;
	struct Coordinates {
		int x, y;
	}XY;
public:
	Neutral(char n, string message, int x_, int y_, int col);
	void message(string message);
	int getX();
	int getY();
};


class Pab : public Neutral
{
public:
	Pab(int &x_max, int &y_max);
	void operator + (Units* unit);
	~Pab();
};

class Tablet : public Neutral
{
public:
	Tablet(int &x_max, int &y_max);
	void operator + (Units* unit);
	~Tablet();
};

class Cave : public Neutral
{
public:
	Cave(int &x_max, int &y_max);
	void operator + (Units* unit);
	~Cave();
};

class Ruin : public Neutral
{
public:
	Ruin(int &x_max, int &y_max);
	void operator + (Units* unit);
	~Ruin();
};