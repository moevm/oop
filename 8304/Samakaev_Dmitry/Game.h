#pragma once
#include "UnitResources.h"


template <typename T>
struct Game
{
	Game(std::vector<std::shared_ptr<Unit>>& first_player_units,
		std::vector<std::shared_ptr<Unit>>& second_player_units)
	{
		rule.setUnits(first_player_units, second_player_units);
	}

	size_t getPlayerNumber()
	{
		return rule.getPlayerNumber();
	}

	std::vector<std::shared_ptr<Unit>>& getCurPlayerUnits()
	{
		return rule.getCurPlayerUnits();
	}

	void changePlayer()
	{
		rule.changePlayer();
	}

	PtsPair getCurPlayerPts()
	{
		return rule.getCurPlayerPts();
	}



private:
	T rule;
	RuleTypes type = RuleTypes::fastGame;
};
