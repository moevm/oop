#pragma once

#include <iostream>
#include <vector>
#include "Game.h"
#include "ClientInput.h"


class GameFacade
{
private:
	bool curPlayer = true; //1 player - true, 2 player - false
	Game* game;

public:
	GameFacade() {
		game = nullptr;
	}
	void switchPlayer() {
		if (!game->isPlayerAlive(curPlayer)) {
			if (curPlayer)
				std::cout << "Facade: player 2 win\n";
			else
				std::cout << "Facade: player 1 win\n";
			return;
		}
		curPlayer ? curPlayer = false : curPlayer = true;

		unsigned isTurn;
		curPlayer ? isTurn = 1 : isTurn = 2;
		game->showField();
		std::cout << isTurn << " Player turn:\n";
	}
	void startNewGame(ClientInput* input) {
		unsigned int cols = input->getCol();
		unsigned int rows = input->getRow();
		unsigned int maxUnits = input->getMaxUnits();
		game = new Game(rows, cols, maxUnits);

		game->addBase(0,0,maxUnits, true);
		game->addBase(cols-1,rows-1, maxUnits, false);

		game->showField();

		std::cout << "1 Player turn:\n";
	}


	void addUnit(ClientInput* input) {
		if (game->addUnit(input->getRow(), input->getCol(), input->getUnitType(), input->getColor(), curPlayer))
			switchPlayer();
	}

	void moveUnit(ClientInput* input){

		if (game->moveUnit(input->getRow(), input->getCol(), input->getRowTo(), input->getColTo(), curPlayer))
			switchPlayer();
	}
	void attackUnit(ClientInput* input) {
		if (game->attack(input->getRow(), input->getCol(), input->getRowTo(), input->getColTo(), curPlayer))
			switchPlayer();
	}
	void healUnit(ClientInput* input) {
		if (game->heal(input->getRow(), input->getCol(), input->getRowTo(), input->getColTo(), curPlayer))
			switchPlayer();
	}
	void getInfo(ClientInput* input) {
		std::string out =  game->getInfoAboutCell(input->getRow(), input->getCol());
		std::cout << out;
	}

	bool isPlayerAlive() {
		return game->isPlayerAlive(curPlayer);
	}



};

