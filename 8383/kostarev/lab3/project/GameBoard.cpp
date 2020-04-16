#include <iostream>
#include "GameBoard.h"
#include "Buildings.h"
#include "Cell.h"
#include "ILandscape.h"
#include "Base.h"

Board::Board(int w, int h) {
	objectOnBoard = 0;
	coin = 2000;
	width = w;
	height = h;
	cells = new Cell * *[height];
	for (int i = 0; i < height; i++) {
		cells[i] = new Cell * [width];
		for (int j = 0; j < width; j++)
			cells[i][j] = new Cell();
	}
}

Board::Board(const Board& old) {
	this->objectOnBoard = old.objectOnBoard;
	this->coin = old.coin;
	this->width = old.width;
	this->height = old.height;
	cells = new Cell * *[height];
	for (int i = 0; i < height; i++) {
		cells[i] = new Cell * [width];
		for (int j = 0; j < width; j++) {
			cells[i][j] = new Cell(*(old.cells[i][j]));
		}
	}
}

Board::Board(Board&& old) {
	this->objectOnBoard = old.objectOnBoard;
	this->coin = old.coin;
	this->width = old.width;
	this->height = old.height;
	cells = new Cell * *[height];
	for (int i = 0; i < height; i++) {
		cells[i] = new Cell * [width];
		for (int j = 0; j < width; j++) {
			cells[i][j] = new Cell(*(old.cells[i][j]));
		}
	}
	old.cells = nullptr;
	old.height = old.width = old.coin = old.objectOnBoard = 0;
}

int Board::getWidth() {
	return width;
}

int Board::getHeight() {
	return height;
}

int Board::getCoin(){
	return coin;
}

int Board::getNumObjects(){
	return objectOnBoard;
}

int Board::getNumBuildings(){
	return buildingsOnBoard;
}

void Board::addCityHall(int x, int y) {
	cells[height - y][x - 1]->addCityHall(width, height);
	objectOnBoard++;
}

bool Board::isCityHall(int x, int y) {
	return cells[height - y][x - 1]->isCityHall();
}

bool Board::addBuild(int x, int y, int xBase, int yBase, Builds type) {
	return dynamic_cast<Base*>(cells[height - yBase][xBase - 1]->getBuildOnCell())->addBuild(x, y, type, this);
}

bool Board::setBuild(int x, int y, IUnit* build) {
	auto proxy = new Proxy(cells[height - y][x - 1]->getLandscape());
	if (proxy->doSomething(build)) {
		if (cells[height - y][x - 1]->getNeutral() != nullptr) {
			cells[height - y][x - 1]->getNeutral()->operator+=(build);
		}
		cells[height - y][x - 1]->addBuild(build);
		for (int i = y - 1; i <= y + 1; i++) {
			if (i > 0 && i <= height) {
				for (int j = x - 1; j <= x + 1; j++) {
					if (j > 0 && j <= width) {
						mediator.Hostility(cells[height - i][j - 1]->getBuildOnCell(), cells[height - y][x - 1]->getBuildOnCell());
					}
				}
			}
		}
		objectOnBoard++;
		buildingsOnBoard++;
		return true;
	}
	return false;
}

void Board::delBuild(int x, int y) {
	cells[height - y][x - 1]->removeBuild();
	objectOnBoard--;
	buildingsOnBoard--;
}

void Board::printBoard() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << cells[i][j]->typeBuild() << ' ';
		}
		std::cout << std::endl;
	}
}

void Board::printAboutCell(int x, int y) {
	cells[height - y][x - 1]->aboutCell();
}
