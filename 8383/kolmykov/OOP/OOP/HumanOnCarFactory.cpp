#include "HumanOnCarFactory.h"



HumanOnCarFactory::HumanOnCarFactory()
{
	type = UnitType::HUMAN_ON_CAR;
}


HumanOnCarFactory::~HumanOnCarFactory()
{
}

std::shared_ptr<Unit> HumanOnCarFactory::create(int x, int y, int level)
{
	return std::shared_ptr<Unit>(new HumanOnCar(x, y, level));
}
