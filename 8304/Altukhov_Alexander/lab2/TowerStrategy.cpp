#include "TowerStrategy.h"

void TowerStrategy::applyEffect(Unit*& target) {
	target->setArmorBuff(5);
}

void TowerStrategy::removeEffect(Unit * &target) {
	target->setArmorBuff(0);
}