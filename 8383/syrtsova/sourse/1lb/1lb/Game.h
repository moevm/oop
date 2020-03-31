#pragma once
#include "Map.h"
#include "Bases.h"

class Game
{
	int x_max, y_max;
public:
	Game();
	void choice_map();
	Map* makeLandscape(int x_max, int y_max, Map* field);
	int select(Bases* base, Map* field);
};

