#pragma once
#include "Field.h"

enum class CreatingUnitResult
{
	IncorrectCoordinates,
	Collision,
	noBase,
	Ok
};

class CreatingUnitChainInterface
{
	virtual CreatingUnitResult execute(Field& fld, int x, int y) = 0;
};


class CreatingUnitBaseCheck : CreatingUnitChainInterface
{
public:
	CreatingUnitResult execute(Field& fld, int x, int y);
};

class CreatingUnitCollisionCheck : CreatingUnitChainInterface
{
	CreatingUnitBaseCheck next;
public:
	CreatingUnitResult execute(Field& fld, int x, int y);
};

class CreatingUnitCoordinatesCheck : CreatingUnitChainInterface
{
	CreatingUnitCollisionCheck next;
public:
	CreatingUnitResult execute(Field& fld, int x, int y);
};