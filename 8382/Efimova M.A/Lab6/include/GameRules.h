#pragma once
#include "Board.h"
class GameRules
{
public:
	virtual int changeTurn() = 0;
	virtual bool checkForEnd() = 0;
	virtual void initBoard(Board* board) = 0;	//std::vector<User> will be aaded as an argument
protected:
	GameRules();
};

