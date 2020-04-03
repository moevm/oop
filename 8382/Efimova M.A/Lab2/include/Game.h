#pragma once
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Board.h"

class UItoBackendConnector;

class Game
{
public:
	static Game* getInstance();
	void initGUI(int argc, char* argv[]);
	void initBoard(int sizeX, int sizeY, int maxAllowedUnits);
	Board* getBoard();
	int Start();
	void _debug_demo();
	void playerAction(Board::BoardCell fromCell, Board::BoardCell toCell, int actionID = -1);
	std::vector<std::pair<int, int>> getCellsToUpdate();
	//void userAction(Board::BoardCell invokingCell, Board::BoardCell targetCell, int actionID = -1);
protected:
	std::vector<std::pair<int, int>> cellsToUpdate;
	static Game* mInstance;
	Board* mGameBoard = nullptr;

	QGuiApplication* _qApp;
	QQmlApplicationEngine* _qEngine;
	UItoBackendConnector* _connector;
};

