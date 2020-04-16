#include "StrongArm.h"



StrongArm::StrongArm()
{
	damage = 200;
	range = 1;
}

StrongArm::StrongArm(const StrongArm & other):Weapon(other) {

}


StrongArm::~StrongArm()
{
}
