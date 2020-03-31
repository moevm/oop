#pragma once
#include "Unit.h"
#include <memory>
#include "UnitType.h"


class UnitFactory
{
protected:
	UnitType type;
public:
	UnitFactory();
	~UnitFactory();
	virtual std::shared_ptr<Unit> create(int x, int y, int level);
	UnitType getType();
};