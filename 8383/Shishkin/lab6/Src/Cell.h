//#pragma once
#ifndef CELL_H
#define CELL_H

#include "Warrior.h"
//#include "Base.h"

class Landscape;
class NeutralObject;
class Base;

class Cell {
public:
	Cell();
	~Cell();
	Cell(const Cell& cell);
	Cell(Cell&& cell);
	Cell& operator= (const Cell& cell);
	Cell& operator= (Cell&& cell);
	void addUnit(Warrior unit);
	void delNeutral();
	bool isUnitFree();
	void setUnit(Warrior w);
	Warrior getUnit() const;
	NeutralObject* getNeutral();
	void setNeutral(NeutralObject* obj);
	Landscape* getLandscape() const;
	void setLandscape(Landscape* value);
	Warrior moveUnit(Warrior w);
	void setBase(Base* base);
	Base* getBase();

private:
	Warrior warrior;
	Landscape* landsc;
	NeutralObject* neutObj;
	Base* base;

};


#endif