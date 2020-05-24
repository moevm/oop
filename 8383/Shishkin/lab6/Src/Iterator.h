//#pragma once
#ifndef ITERATOR_H
#define ITERATOR_H

#include "Warrior.h"
#include "Field.h"

class Iterator {
public:
	Iterator();
	~Iterator();
	Iterator(Cell** cell, int x, int y);
	void first();
	void last();
	void next();
	Cell* getCell();
	bool getIsEnd();
	int getX();
	int getY();
	void displayUnitData(Field& f1);
	void checkWin(Field& f1, bool& win1st, bool& win2nd);

private:
	int x, y;
	int maxX, maxY;
	bool isEnd;
	Cell** cell;
};

#endif