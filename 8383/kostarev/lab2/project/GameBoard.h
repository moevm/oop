#pragma once
#include <vector>
#include "Cell.h"

class Board {
private:
	int width;
	int height;
	int objectOnBoard;
	int coin;
	Cell*** cells;
public:
	Board(int w, int h);
	Board(const Board& old);
	Board(Board&& before);
	~Board() = default;
	int getWidth();
	int getHeight();
	void newCityHall();
	void newBuild();
	bool setBuild(int x, int y, IUnit* build);
	void delBuild();
	void info();
};