#include "CreatingUnitChain.h"

CreatingUnitResult CreatingUnitCollisionCheck::execute(Field& fld, int x, int y)
{
	if (fld.getUNIT_FIELD()[x + fld.getX_SIZE() * y] != nullptr)
		return CreatingUnitResult::Collision;

	return next.execute(fld, x, y);
}

CreatingUnitResult CreatingUnitCoordinatesCheck::execute(Field& fld, int x, int y)
{
	if (x < 0 || x >= fld.getX_SIZE() || y < 0 || y >= fld.getY_SIZE())
		return CreatingUnitResult::IncorrectCoordinates;

	return next.execute(fld, x, y);
}

CreatingUnitResult CreatingUnitBaseCheck::execute(Field& fld, int x, int y)
{
	if (fld.getCELL_BASE()[x + y * fld.getX_SIZE()] == nullptr)
		return CreatingUnitResult::noBase;

	return CreatingUnitResult::Ok;
}
