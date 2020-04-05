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

void Board::newCityHall() {
	int x, y;
	std::cout << "ADD CITY HALL, Enter x, y:" << std::endl;
	std::cin >> x >> y;
	if (x > width || y > height || x < 1 || y < 1) {
		std::cout << "WARNING!" << std::endl;
		return;
	}
	cells[height - y][x - 1]->addCityHall(width,height);
	objectOnBoard++;
	coin -= 300;
}

void Board::newBuild() {
	int x, y;
	std::cout << "Select a base (city hall), Enter x, y:" << std::endl;
	std::cin >> x >> y;
	if (x > width || y > height || x < 1 || y < 1) {
		std::cout << "WARNING!" << std::endl;
		return;
	}
	if (cells[height - y][x - 1]->isCityHall()) {
		int xNew, yNew;
		int type;
		std::cout << "Add Build, Enter x, y and type of Building (D-0, H-1, F-2, O-3, P-4, S-5, V-6):" << std::endl;
		std::cin >> xNew >> yNew >> type;
		auto cityHall = cells[height - y][x-1]->getBuildOnCell();
		if (cells[height - y][x - 1]->getNeutral() != nullptr) {
			std::cout << "Neutral object on cell: " << cells[height - y][x - 1]->getNeutral()->typeOfNeutrals() << std::endl;
			std::cout << "(0 - chernozem, 1 - relics, 2 - radiation, 3 - gas)" << std::endl;
		}
		dynamic_cast<Base*>(cityHall)->addBuild(xNew, yNew, static_cast<Builds>(type), this);
	}
	else {
		std::cout << "It isn't City Hall!" << std::endl;
	}
}

bool Board::setBuild(int x, int y, IUnit* build) {
	auto proxy = new Proxy(cells[height - y][x - 1]->getLandscape());
	if (proxy->doSomething(build)) {
		if (cells[height - y][x - 1]->getNeutral() != nullptr) {
			cells[height - y][x - 1]->getNeutral()->operator+=(build);
		}
		cells[height - y][x - 1]->addBuild(build);
		objectOnBoard++;
		return true;
	}
	return false;
}

void Board::delBuild() {
	int x, y;
	std::cout << "DEL BUILD, Enter x, y:" << std::endl;
	std::cin >> x >> y;
	if (x > width || y > height || x < 1 || y < 1) {
		std::cout << "WARNING!" << std::endl;
		return;
	}
	cells[height - y][x - 1]->removeBuild();
	objectOnBoard--;
}

void Board::info() {
	std::cout << "Buildings on board: " << objectOnBoard << std::endl;
	std::cout << "Coin: " << coin << std::endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << cells[i][j]->typeBuild() << ' ';
		}
		std::cout << std::endl;
	}
	bool about = true;
	std::cout << "You want to know more about the individual cell? (1 - yes, 0 - no)" << std::endl;
	std::cin >> about;
	while (about) {
		int x, y;
		std::cout << "Enter x, y:" << std::endl;
		std::cin >> x >> y;
		cells[height - y][x - 1]->aboutCell();
		std::cout << "You want to know more about the individual cell? (1 - yes, 0 - no)" << std::endl;
		std::cin >> about;
	}
}
