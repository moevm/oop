#pragma once
#include "UnitParent.h"
#include <vector>

#define UNITS_MAX 7

class Vector2D;
class GameField;


class UnitsFactory {
public:
	virtual FlyingUnits *createFlyingUnit() = 0;
	virtual GroundUnits *createGroundUnit() = 0;
	virtual SmallUnits *createSmallUnit() = 0;
	~UnitsFactory() {}
};

class UnitsFactoryLigth : public UnitsFactory {
public:
	FlyingUnits *createFlyingUnit() {
		return new BeeUnit;
	}

	GroundUnits *createGroundUnit() {
		return new FlowerUnit;
	}

	SmallUnits *createSmallUnit() {
		return new SprinklerUnit;
	}
};

class UnitsFactoryDew : public UnitsFactory {
public:
	FlyingUnits *createFlyingUnit() {
		return new FlyUnit;
	}

	GroundUnits *createGroundUnit() {
		return new CoalUnit;
	}

	SmallUnits *createSmallUnit() {
		return new CollectorUnit;
	}

};

class GameUnits {
public:
	std::vector<UnitParent*> units;
	int currentUnitIndex;
	Vector2D borders;

	UnitsFactoryLigth unitsFactoryLigth;
	UnitsFactoryDew unitsFactoryDew;

	void updateBorders(Vector2D fieldBorders);
	void switchUnit(bool forward);
	bool createUnit(char type, Vector2D location);
	bool moveUnit(Vector2D direction);

	UnitParent *getUnit(Vector2D location);
	GameUnits(std::string unitsFileName, Vector2D fieldBorders);
	GameUnits(Vector2D fieldBorders, GameField *field);
	~GameUnits();

private:
	int overlapCheck(Vector2D targetLocation);
	GameField *field;
};

