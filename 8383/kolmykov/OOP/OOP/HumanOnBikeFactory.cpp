#include "HumanOnBikeFactory.h"



HumanOnBikeFactory::HumanOnBikeFactory()
{
	type = UnitType::HUMAN_ON_BIKE;
}


HumanOnBikeFactory::~HumanOnBikeFactory()
{
}

std::shared_ptr<Unit> HumanOnBikeFactory::create(int x, int y, int level)
{
	return std::shared_ptr<Unit>(new HumanOnBike(x, y, level));
}
