#pragma once

struct Point
{
	int x;
	int y;
};

enum class takeDamageResult : int
{
	damageTaken,
	block,
	dodge,
	death
};

enum class addAndRemoveResult : int
{
	addErrorColission,
	removeErrorNoUnit,
	unitAdded,
	unitRemoved
};

enum class moveResult : int
{
	moveComplete,
	moveCoordinateError
};
