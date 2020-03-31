#include "Sword.h"



Sword::Sword() {
	range = 1;
	damage = 150;
}

Sword::Sword(const Sword & other):Weapon(other) {

}


Sword::~Sword()
{
}
