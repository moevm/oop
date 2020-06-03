#pragma once
#include "PlayableBoardUnit.h"
#include "BoardUnitFactory.h"
class Cavalry : public PlayableBoardUnit
{
public:
	Cavalry() {};
	ActionMeta turnAction() override;
};

class HeavyCavalry : public Cavalry
{
public:
	HeavyCavalry();
	ActionMeta userAction() override;
	ActionMeta defend(ActionMeta) override;
	BoardUnit* getCopy() override;
};

class LightCavalry : public Cavalry
{
public:
	LightCavalry();
	ActionMeta userAction() override;
	ActionMeta defend(ActionMeta) override;
	BoardUnit* getCopy() override;
};

class CavalryFactory : public BoardUnitFactory //фабрика
{
public:
	CavalryFactory() {};
	BoardUnit* getType(int type) override;
};

