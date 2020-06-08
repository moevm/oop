#pragma once
#include "Field.h"

enum class CreatingBaseResult
{
	IncorrectCoordinates,
	Collision,
	Ok
};

class CreatingBaseInterface
{
public:
	virtual CreatingBaseResult execute(Field& fld, int x, int y) = 0;
};

class CreatingBaseColissionCheck : CreatingBaseInterface
{
public:
	CreatingBaseResult execute(Field& fld, int x, int y);
};

class CreatingBaseCorrdinatesCheck : CreatingBaseInterface
{
	CreatingBaseColissionCheck next;
public:
	CreatingBaseResult execute(Field& fld, int x, int y);
};
