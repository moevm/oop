#pragma once
#include "Field.h"
#include "CreatingUnitChain.h"
#include "MovingUnitChain.h"
#include "CreatingBaseChain.h"

class Fasad
{
	Field fld = Field(10, 10);
	CreatingUnitCoordinatesCheck CUCC;
	MovingUnitCoordinatesCheck MUCC;
	CreatingBaseCorrdinatesCheck CBCC;

public:
	Fasad();

	CreatingUnitResult createUnit(int x, int y, Unit* unit);
	MovingUnitResult moveUnit(int x_from, int y_from, int x_to, int y_to);
	CreatingBaseResult createBase(int x, int y);

	bool deleteUnit(int x, int y);
	bool relaxUnit(int x, int y);
	bool notifyBase(int x, int y);
	Field::Snapshot* saveState();
	bool loadState(Field::Snapshot* snap);

	void printFld();
};

