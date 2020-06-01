#include "GameRulesRandom.h"
#include "PongoBaseBoardUnit.h"
#include <random>

GameRulesRandom::GameRulesRandom(Board* board) : _board(board) {}

int GameRulesRandom::changeTurn() {
	std::random_device rd;
	std::mt19937_64 mt_rand(rd());
	std::uniform_int_distribution<> rand(1, 4);		//(1, numOfPlayers)
	return rand(mt_rand);
}

int GameRulesRandom::checkForEnd() {
	std::random_device rd;
	std::mt19937_64 mt_rand(rd());
	std::uniform_int_distribution<> rand(0, 1);
	return rand(mt_rand);
}

void GameRulesRandom::initBoard() {
	std::random_device rd;
	std::mt19937_64 mt_rand(rd());
	std::uniform_int_distribution<> rand(0, 100);

	/*for (int i = 0; i < board->getBoardProperties().sizeY; i++) {
		for (int j = 0; j < board->getBoardProperties().sizeX; j++) {
			if (rand(mt_rand) < 20) {
				//auto base = new PongoBaseBoardUnit();
				//board->addUnit(base, j, i);
				//cnnect created base to specific user;
			}
		}
	}*/
}