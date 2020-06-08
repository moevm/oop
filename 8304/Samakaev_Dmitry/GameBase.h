#pragma once
#include "unit_base.h"
#include <vector>
#include <algorithm>
#include <iostream>

class GameBase
{
	std::vector<Unit*> units;
	int hp = 1000;
	int max_units_cnt = 5;

public:
	GameBase(size_t ind);
	bool subscribe(Unit*);
	void unsubscribe(Unit*);
	void notify();

	size_t ind;
};

