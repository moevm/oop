#pragma once
#include "PlayableBoardUnit.h"
#include "BoardUnitFactory.h"
class Infantry : public PlayableBoardUnit
{
public:
	Infantry() {}; //пехота
	ActionMeta turnAction() override;
};

class Swordsman : public Infantry 
{
public:
	Swordsman();//фехтовальщики
	ActionMeta userAction() override;
	ActionMeta defend(ActionMeta) override;
	BoardUnit* getCopy() override;
};

class Spearman : public Infantry
{
public:
	Spearman();//копьеносцы
	ActionMeta userAction() override;
	ActionMeta defend(ActionMeta) override;
	BoardUnit* getCopy() override;
};
//какой тип нам надо вызвать в дальнейшем
class InfantryFactory : public BoardUnitFactory
{
public:
	InfantryFactory() {};
	BoardUnit* getType(int type) override;
};

