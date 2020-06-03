#pragma once
#include "Object.h"
#include "Unit.h"
#include "AbstractFactory.h"

class GameField {
protected:
	int width, height;
	int step;
	int maxUnits;
	Object*** field;						//двумерный массив указателей
public:
	GameField();
	GameField(int height, int width);
	GameField(const GameField& other);		//конструктор копирования
	GameField(GameField&& other);			//конструктор переноса
	void createField();
	Unit* createUnit(char view, int type);
	int addUnit(Object* unit, int x, int y);
	int movingUnit(int x, int y, char course, int steps);
	int deleteUnit(int x, int y);
	void printCurField();
	int getHeight();
	int getWidth();
	int getStep();
	int getMaxUnits();
	~GameField();

};
