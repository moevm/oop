#pragma once
#include "PlayableBoardUnit.h"
class PongoBaseBoardUnit;
class PongoBoardUnit : public PlayableBoardUnit
{
public:
	PongoBoardUnit(PongoBaseBoardUnit* base);
protected:
	PongoBaseBoardUnit* _base;
};

