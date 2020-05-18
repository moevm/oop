#pragma once
#include "GameRules.h"
class GameRulesRandom : public GameRules
{
public:
	GameRulesRandom();
	int changeTurn() override;
	bool checkForEnd() override;
	void initBoard(Board* board) override;
};

