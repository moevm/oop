#pragma once
#include "PongoBoardUnit.h"
#include "BoardUnitFactory.h"
class PongoBaseBoardUnit;

class Infantry : public PongoBoardUnit
{
public:
	Infantry(PongoBaseBoardUnit* base);
	std::vector<ActionMeta> turnAction() override;
};

class Swordsman : public Infantry
{
public:
	Swordsman(PongoBaseBoardUnit* base);
	std::vector<ActionMeta> userAction(Board::BoardCell targetCell, int action = -1) override;
	std::vector<ActionMeta> defend(ActionMeta) override;
	BoardUnit* getCopy() override;
	std::string getName() override;
};

class Spearman : public Infantry
{
public:
	Spearman(PongoBaseBoardUnit* base);
	std::vector<ActionMeta> userAction(Board::BoardCell targetCell, int action = -1) override;
	std::vector<ActionMeta> defend(ActionMeta) override;
	BoardUnit* getCopy() override;
	std::string getName() override;
};

class InfantryFactory : public BoardUnitFactory
{
public:
	InfantryFactory(PongoBaseBoardUnit* base) : BoardUnitFactory(base) {};
	PlayableBoardUnit* createUnit(int type) override;
};

