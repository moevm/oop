#include "GameRulesClassic.h"
#include <random>
#include "Logger.h"

GameRulesClassic::GameRulesClassic(std::vector<User*> users, Board* board) : _users(users), _board(board) {

}

int GameRulesClassic::changeTurn() {
	int prevTurn = currentTurn;
	if (currentTurn == _users.size() - 1)
		currentTurn = 0;
	else
		currentTurn++;
	Logger::log("GameRulesClassic", "Changing turn from " + std::to_string(prevTurn) + " to " + std::to_string(currentTurn));
	return currentTurn;
}

int GameRulesClassic::checkForEnd() {
	std::vector<int> numBases(_users.size());
	for (int i = 0; i < _users.size(); i++)
		numBases[i] = 0;

	for (int i = 0; i < _board->getBoardProperties().sizeX; i++) {
		for (int j = 0; j < _board->getBoardProperties().sizeY; j++) {
			auto cell = _board->getCellAt(i, j);
			if (!cell.isEmpty) {
				auto unit = cell.unit;
				auto base = dynamic_cast<PongoBaseBoardUnit*>(unit);
				if (base != nullptr) {
					for (int k = 0; k < _users.size(); k++) {
						if (base->getUser() == _users[k])
							numBases[k]++;
					}
				}
			}
		}
	}

	for (int i = 0; i < _users.size(); i++) {
		if (numBases[i] == 0)
			return i;
	}
	return -1;
}

void GameRulesClassic::initBoard() {
	std::random_device rd;
	std::mt19937_64 mt_rand(rd());
	std::uniform_int_distribution<> x_rand(1, _board->getBoardProperties().sizeX-1);
	std::uniform_int_distribution<> y_rand(1, _board->getBoardProperties().sizeY-1);
	for (int i = 0; i < _users.size(); i++) {
		auto base = new PongoBaseBoardUnit(_users[i]);
		int x = x_rand(mt_rand);
		int y = y_rand(mt_rand);
		if (!_board->getCellAt(x, y).isEmpty)
			_board->removeUnit(x, y);
		_board->addUnit(base, x, y);
	}
}