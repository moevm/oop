#include "CreatingBaseChain.h"

CreatingBaseResult CreatingBaseCorrdinatesCheck::execute(Field& fld, int x, int y)
{
	if (x < 0 || y < 0 || x >= fld.getX_SIZE() || y >= fld.getY_SIZE())
		return CreatingBaseResult::IncorrectCoordinates;

	return next.execute(fld, x, y);
}

CreatingBaseResult CreatingBaseColissionCheck::execute(Field& fld, int x, int y)
{
	if (fld.getCELL_BASE()[x + y * fld.getX_SIZE()] != nullptr)
		return CreatingBaseResult::Collision;

	return CreatingBaseResult::Ok;
}
