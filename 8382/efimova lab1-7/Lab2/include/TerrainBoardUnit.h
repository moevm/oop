#pragma once
#include "BoardUnit.h"
class TerrainBoardUnit : public BoardUnit
{
public:
	enum class TerrainType {Grass, River, Swamp, Mountain, Volcano}; //перечисление с помощью enum
	virtual bool isPassable() = 0;
	//UnitType getType() override;
};

