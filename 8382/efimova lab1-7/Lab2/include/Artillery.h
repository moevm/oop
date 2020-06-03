#pragma once
#include "PongoBoardUnit.h"
#include "BoardUnitFactory.h"
class PongoBaseBoardUnit;

class Artillery : public PongoBoardUnit
{
public:
	Artillery(PongoBaseBoardUnit* base);	//!!!
	std::vector<ActionMeta> turnAction() override;
};

class Catapult : public Artillery
{
public:
	Catapult(PongoBaseBoardUnit* base);
	std::vector<ActionMeta> userAction(Board::BoardCell targetCell, int action = -1) override;
	std::vector<ActionMeta> defend(ActionMeta) override;
	BoardUnit* getCopy() override;
	std::string getName() override;
};

class Cannon : public Artillery
{
public:
	Cannon(PongoBaseBoardUnit* base);
	std::vector<ActionMeta> userAction(Board::BoardCell targetCell, int action = -1) override;
	std::vector<ActionMeta> defend(ActionMeta) override;
	BoardUnit* getCopy() override;
	std::string getName() override;
};

class ArtilleryFactory : public BoardUnitFactory
{
public:
	ArtilleryFactory(PongoBaseBoardUnit* base) : BoardUnitFactory(base) {};
	PlayableBoardUnit* createUnit(int type) override;
};

