#pragma once
#include "TerrainBoardUnit.h"
class Grass : public TerrainBoardUnit
{public:
	Grass() {};
	BoardUnit* getCopy() override;
	std::vector<ActionMeta> turnAction() override;
	bool isPassable() override;
	//TerrainType getTerrainType() override;
};

