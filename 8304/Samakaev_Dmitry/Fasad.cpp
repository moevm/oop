#include "Fasad.h"

Fasad::Fasad()
{}

CreatingUnitResult Fasad::createUnit(int x, int y, Unit* unit)
{
	auto res = CUCC.execute(fld, x, y);
	if (res == CreatingUnitResult::Ok)
		fld.add_base_unit(unit, x, y);	

	return res;
}

MovingUnitResult Fasad::moveUnit(int x_from, int y_from, int x_to, int y_to)
{
	auto res = MUCC.execute(fld, x_from, y_from, x_to, y_to);
	if (res == MovingUnitResult::Ok)
		fld.relocate_unit(x_from, y_from, x_to, y_to);
	
	return res;
}

CreatingBaseResult Fasad::createBase(int x, int y)
{
	auto res = CBCC.execute(fld, x, y);

	if (res == CreatingBaseResult::Ok)
	{
		GameBase* base = new GameBase(x + fld.getX_SIZE() * y);
		fld.add_base(base, x, y);
	}

	return res;
}

bool Fasad::deleteUnit(int x, int y)
{
	bool res = false;
	
	if (x < 0 || y < 0 || x >= fld.getX_SIZE() || y >= fld.getY_SIZE())
		return false;

	if (fld.getUNIT_FIELD()[x + fld.getX_SIZE() * y] != nullptr)
	{
		fld.delete_unit(x, y);
		res = true;
	}

	return res;
}

bool Fasad::relaxUnit(int x, int y)
{
	bool res = false;
	Unit* cur = fld.getUNIT_FIELD()[x + fld.getX_SIZE() * y];

	if (cur != nullptr)
	{
		cur->hp.change(cur->hp.get() + 20);
		res = true;
	}

	return res;
}

bool Fasad::notifyBase(int x, int y)
{
	bool res = false;
	GameBase* cur = fld.getCELL_BASE()[x + fld.getX_SIZE() * y];

	if (cur != nullptr)
	{
		cur->notify();
		res = true;
	}

	return res;
}

Field::Snapshot* Fasad::saveState()
{
	return fld.saveState();
}

bool Fasad::loadState(Field::Snapshot* snap)
{
	return fld.loadState(snap);
}

void Fasad::printFld()
{
	std::cout << fld;
}
