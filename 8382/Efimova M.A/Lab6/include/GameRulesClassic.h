#pragma once
#include "GameRules.h"
class GameRulesClassic : public GameRules
{
public:
	GameRulesClassic();
	int changeTurn() override;
	bool checkForEnd() override;
	void initBoard(Board* board) override;
};

