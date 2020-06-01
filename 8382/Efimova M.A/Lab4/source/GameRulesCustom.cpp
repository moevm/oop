#include "GameRulesCustom.h"

template <std::vector<User*> * users, Board * board, int turnChangeType, int endCriteriaType, std::vector<int> * boardInitArgs>
GameRulesCustom<users, board, turnChangeType, endCriteriaType, boardInitArgs>::GameRulesCustom() {}

template <std::vector<User*> * users, Board * board, int turnChangeType, int endCriteriaType, std::vector<int> * boardInitArgs>
int GameRulesCustom<users, board, turnChangeType, endCriteriaType, boardInitArgs>::changeTurn() {
	switch (turnChangeType) {
	case 0: 
	{
		int prevTurn = currentTurn;
		if (currentTurn == users->size() - 1)
			currentTurn = 0;
		else
			currentTurn++;
		Logger::log("GameRulesClassic", "Changing turn from " + std::to_string(prevTurn) + " to " + std::to_string(currentTurn));
		return currentTurn;
	}

	case 1:
	{
		std::random_device rd;
		std::mt19937_64 mt_rand(rd());
		std::uniform_int_distribution<> rand(1, users->size());		//(1, numOfPlayers)
		return rand(mt_rand);
	}
	}
}

template <std::vector<User*> * users, Board * board, int turnChangeType, int endCriteriaType, std::vector<int> * boardInitArgs>
int GameRulesCustom<users, board, turnChangeType, endCriteriaType, boardInitArgs>::checkForEnd() {
	switch (endCriteriaType) {
	case 0:
	{
		std::vector<int> numBases(users->size());
		for (int i = 0; i < users->size(); i++)
			numBases[i] = 0;

		for (int i = 0; i < board->getBoardProperties().sizeX; i++) {
			for (int j = 0; j < board->getBoardProperties().sizeY; j++) {
				auto cell = board->getCellAt(i, j);
				if (!cell.isEmpty) {
					auto unit = cell.unit;
					auto base = dynamic_cast<PongoBaseBoardUnit*>(unit);
					if (base != nullptr) {
						for (int k = 0; k < users->size(); k++) {
							if (base->getUser() == (*users)[k])
								numBases[k]++;
						}
					}
				}
			}
		}

		for (int i = 0; i < users->size(); i++) {
			if (numBases[i] == 0)
				return i;
		}
		return -1;
	}

	case 1:
	{
		std::random_device rd;
		std::mt19937_64 mt_rand(rd());
		std::uniform_int_distribution<> rand(-1, users->size());
		return rand(mt_rand);
	}
	}
}

template <std::vector<User*> * users, Board * board, int turnChangeType, int endCriteriaType, std::vector<int> * boardInitArgs>
void GameRulesCustom<users, board, turnChangeType, endCriteriaType, boardInitArgs>::initBoard() {
	if (boardInitArgs->empty()) {
		std::random_device rd;
		std::mt19937_64 mt_rand(rd());
		std::uniform_int_distribution<> x_rand(1, board->getBoardProperties().sizeX - 1);
		std::uniform_int_distribution<> y_rand(1, board->getBoardProperties().sizeY - 1);
		for (int i = 0; i < users->size(); i++) {
			auto base = new PongoBaseBoardUnit((*users)[i]);
			int x = x_rand(mt_rand);
			int y = y_rand(mt_rand);
			if (!board->getCellAt(x, y).isEmpty)
				board->removeUnit(x, y);
			board->addUnit(base, x, y);
		}
	}
}