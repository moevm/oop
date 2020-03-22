#include "SpittingToEnemyHead.h"



SpittingToEnemyHead::SpittingToEnemyHead()
{
	range = 5;
	damage = 120;
}

SpittingToEnemyHead::SpittingToEnemyHead(const SpittingToEnemyHead & other):Weapon(other) {

}


SpittingToEnemyHead::~SpittingToEnemyHead()
{
}
