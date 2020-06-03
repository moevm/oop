#pragma once
#include "PlayableBoardUnit.h"
#include "PongoBaseBoardUnit.h"
class PongoBoardUnit : public PlayableBoardUnit
{
public:
	PongoBoardUnit(PongoBaseBoardUnit* base);
protected:
	PongoBaseBoardUnit* _base;
};

