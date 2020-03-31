#include "HumanWithBatFactory.h"



HumanWithBatFactory::HumanWithBatFactory()
{
	type = UnitType::HUMAN_WITH_BAT;
}


HumanWithBatFactory::~HumanWithBatFactory()
{
}

std::shared_ptr<Unit> HumanWithBatFactory::create(int x, int y, int level)
{
	return std::shared_ptr<Unit>(new HumanWithBat(x, y, level));
}
