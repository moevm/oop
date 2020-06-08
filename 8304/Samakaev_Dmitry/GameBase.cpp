#include "GameBase.h"

GameBase::GameBase(size_t ind) : ind(ind)
{
}

bool GameBase::subscribe(Unit* unit)
{
	if (units.size() >= 5)
	{
		std::cout << "Reached max base units cnt\n";
		return false;
	}
	units.push_back(unit);
	return true;
}

void GameBase::unsubscribe(Unit* unit)
{
	auto it = std::find(units.begin(), units.end(), unit);
	if (it != units.end())
	{
		units.erase(it);
	}
}

void GameBase::notify()
{
	for (auto& unit : units)
		unit->damage.change(unit->damage.get() + 5);
}
