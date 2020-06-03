#pragma once
#include "TerrainBoardUnit.h"
class River : public TerrainBoardUnit
{
public:
	River() {};
	BoardUnit* getCopy() override;
	std::vector<ActionMeta> turnAction() override;
	bool isPassable() override;
	std::string getName() override;
};

