#pragma once
#include <vector>
#include "Cell.h"
#include "Mediator.h"

class Board {
private:
	int width;
	int height;
	int objectOnBoard;
	int buildingsOnBoard;
	int coin;
	Cell*** cells;
	Mediator mediator;
public:
	Board(int w, int h);
	Board(const Board& old);
	Board(Board&& before);
	~Board() = default;
	int getWidth();
	int getHeight();
	int getCoin();
	int getNumObjects();
	int getNumBuildings();
	bool isCityHall(int x, int y);
	void addCityHall(int x, int y);
	bool addBuild(int x, int y, int xBase, int yBase, Builds type);
	bool setBuild(int x, int y, IUnit* build);
	void delBuild(int x, int y);
	void printBoard();
	void printAboutCell(int x, int y);
};