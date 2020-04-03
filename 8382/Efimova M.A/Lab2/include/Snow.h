#pragma once
#include "TerrainBoardUnit.h"
class Snow : public TerrainBoardUnit
{
public:
	Snow() {};
	BoardUnit* getCopy() override;
	std::vector<ActionMeta> turnAction() override;
	bool isPassable() override;
	std::string getName() override;
};

