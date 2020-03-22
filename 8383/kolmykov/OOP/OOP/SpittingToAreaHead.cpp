#include "SpittingToAreaHead.h"



SpittingToAreaHead::SpittingToAreaHead() {
	range = 3;
	damage = 120;
}

SpittingToAreaHead::SpittingToAreaHead(const SpittingToAreaHead & other):Weapon(other)
{
}


SpittingToAreaHead::~SpittingToAreaHead()
{
}
