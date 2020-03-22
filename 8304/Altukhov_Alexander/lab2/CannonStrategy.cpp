#include "CannonStrategy.h"
#include <iostream>
void CannonStrategy::applyEffect(Unit*& target) {
	target->setAttackBuff(5);

}

void CannonStrategy::removeEffect(Unit*& target) {

	target->setAttackBuff(0);
}