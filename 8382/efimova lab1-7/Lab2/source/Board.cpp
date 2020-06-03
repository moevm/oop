#include "Board.h"
#include "Reputeless/PerlinNoise.hpp"	//Perlin noise header library
#include <QDebug>
#include <string>

Board::Board(BoardProperties* properties) : mBoardProperties(properties) {
	boardArray = new BoardCell * [properties->sizeY];
	for (int i = 0; i < properties->sizeY; i++) {
		BoardCell* tCellArray = new BoardCell[properties->sizeX];
		boardArray[i] = tCellArray;
	}
	siv::PerlinNoise mNoise;
	std::random_device rd;
	std::mt19937_64 mt_rand(rd());
	std::uniform_int_distribution<> rand_1(0, mBoardProperties->sizeX * mBoardProperties->sizeY);
	std::uniform_int_distribution<> rand_2(1, 4);
	mNoise.reseed(mt_rand());	
	for (int i = 0; i < mBoardProperties->sizeY; i++) {
		for (int j = 0; j < mBoardProperties->sizeX; j++) {
			boardArray[i][j].x = j;
			boardArray[i][j].y = i;
			//auto value = mNoise.normalizedOctaveNoise2D_0_1((double)j/10, (double)i/10, 100);
			auto value = mNoise.normalizedOctaveNoise2D_0_1((double)j / 10, (double)i / 10, 1000);
			if(value >= 0.5)
				boardArray[i][j].terrainUnit = new Grass();
			else
				boardArray[i][j].terrainUnit = new Snow();

			if (rand_1(mt_rand) <= (double)mBoardProperties->sizeX * (double)mBoardProperties->sizeY * 0.05 && boardArray[i][j].isEmpty) {
				switch (rand_2(mt_rand)) {
				case 1:
					boardArray[i][j].unit = new Stone();
					boardArray[i][j].isEmpty = false;
					break;
				case 2:
					boardArray[i][j].unit = new Tree();
					boardArray[i][j].isEmpty = false;
					break;
				case 3:
					boardArray[i][j].unit = new TreeLog();
					boardArray[i][j].isEmpty = false;
					break;
				default:
					break;
				}
			}
		}
	}
}

void Board::addUnit(BoardUnit* newUnit, unsigned int x, unsigned int y) {
	qInfo() << "Adding unit" << newUnit->getName().c_str() << "at" << x << y;
	BoardCell* tCell = &(boardArray[y][x]);
	if (unitCount >= mBoardProperties->maxAllowedUnits) {
		//throw
		qInfo() << "Board error: tried to add unit when maximum number of units is reached";
		return;
	}
	if (!tCell->isEmpty) {
		//throw
		qInfo() << "Board error: tried to add unit inside a non-empty cell";
		return;
	}
	tCell->isEmpty = false;
	tCell->unit = newUnit;
	unitCount++;
}

void Board::removeUnit(unsigned int x, unsigned int y) {
	BoardCell* tCell = &(boardArray[y][x]);
	if (tCell->isEmpty) {
		//throw
		qInfo() << "Board error: tried to remove unit from an empty cell";
		return;
	}
	tCell->isEmpty = true;
	tCell->unit = nullptr;
}

void Board::removeUnit(BoardUnit* unit) {
	BoardCell* tCell = nullptr;
	for (int i = 0; i < mBoardProperties->sizeY; i++) {
		for (int j = 0; j < mBoardProperties->sizeX; j++) {
			if (boardArray[i][j].unit == unit) {
				tCell = &boardArray[i][j];
			}
		}
	}
	if (tCell == nullptr || tCell->isEmpty) {
		qInfo() << "Board error: tried to remove unit from an empty cell";
		return;
	}
	tCell->isEmpty = true;
	tCell->unit = nullptr;
}

BoardUnit* Board::operator()(unsigned int x, unsigned int y) {
	if (x > mBoardProperties->sizeX || y > mBoardProperties->sizeY) {
		//throw
		return nullptr;
	}
	return boardArray[y][x].unit;
}

Board::Board(Board& board) : unitCount(board.unitCount), freeCells(board.freeCells)	//does not work!!
{
	mBoardProperties = new BoardProperties(*(board.mBoardProperties));
	boardArray = new BoardCell * [mBoardProperties->sizeY];
	for (int i = 0; i < mBoardProperties->sizeY; i++) {
		BoardCell* tCellArray = new BoardCell[mBoardProperties->sizeX];
		boardArray[i] = tCellArray;
		for (int j = 0; j < mBoardProperties->sizeX; j++) {
			if (!board.boardArray[i][j].isEmpty) {
				boardArray[i][j].isEmpty = false;
				boardArray[i][j].unit = board.boardArray[i][j].unit->getCopy();
				boardArray[i][j].terrainUnit = (TerrainBoardUnit*)(board.boardArray[i][j].terrainUnit->getCopy());
			}
		}
	}
}

void Board::moveUnit(BoardUnit* unit, unsigned int x, unsigned int y) {
	BoardCell* fromCell = nullptr;
	BoardCell* toCell = &boardArray[y][x];
	for (int i = 0; i < mBoardProperties->sizeY; i++) {
		for (int j = 0; j < mBoardProperties->sizeX; j++) {
			if (boardArray[i][j].unit == unit) {
				fromCell = &boardArray[i][j];
			}
		}
	}
	if (fromCell == nullptr || fromCell->isEmpty || !toCell->isEmpty) {
		qInfo() << "Board error: tried to move unit but something went wrong";
		return;
	}
	toCell->isEmpty = false;
	toCell->unit = fromCell->unit;
	fromCell->unit = nullptr;
	fromCell->isEmpty = true;
}

void Board::moveUnit(unsigned int current_x, unsigned int current_y, unsigned int intended_x, unsigned int intended_y) {
	BoardCell* fromCell = &boardArray[current_y][current_x];;
	BoardCell* toCell = &boardArray[intended_y][intended_x];
	if (fromCell->isEmpty || !toCell->isEmpty) {
		qInfo() << "Board error: tried to move unit but something went wrong";
		return;
	}
	toCell->isEmpty = false;
	toCell->unit = fromCell->unit;
	fromCell->unit = nullptr;
	fromCell->isEmpty = true;
}

void Board::_debug_print() {
	qInfo() << "--------------------Board start----------------------";
	for (int i = 0; i < mBoardProperties->sizeY; i++) {
		std::string tstr;
		for (int j = 0; j < mBoardProperties->sizeX; j++) {
			if (boardArray[i][j].isEmpty) {
				tstr += "[ ]";
			}
			else
				tstr += "[X]";
			tstr += " ";
		}
		qInfo() << " ";
		qInfo() << tstr.c_str();
	}
	qInfo() << " ";
	qInfo() << "--------------------Board end----------------------";
	qInfo() << " ";
}

Board::BoardCell Board::getCellAt(unsigned int x, unsigned int y) {
	return boardArray[y][x];
}

std::pair<int, int> Board::getUnitCoords(BoardUnit* unit) {
	std::pair<int, int> coords;
	for (int i = 0; i < mBoardProperties->sizeY; i++) {
		for (int j = 0; j < mBoardProperties->sizeX; j++) {
			if (boardArray[i][j].unit == unit || boardArray[i][j].terrainUnit == unit) {
				coords = std::pair<int, int>(j, i);
			}
		}
	}
	return coords;
}




