#include "NeutralObject.h"
#include <iostream>
NeutralObjectTypes NeutralObject::getNeutralObjectType() {
	return type;
}

void NeutralObject::setNeutralObjectType(NeutralObjectTypes type) {
	this->type = type;
}

void NeutralObject::selectStrategy() {

	if (type == NeutralObjectTypes::TOWER) {
		strategy = new TowerStrategy;
	}
	else if (type == NeutralObjectTypes::WEAPONRY) {
		strategy = new WeaponryStrategy;
	}
	else if (type == NeutralObjectTypes::GUN) {
		strategy = new GunStrategy;
	}
	else if (type == NeutralObjectTypes::SHRINE) {
		strategy = new ShrineStrategy;
	}
}
void NeutralObject::applyEffect(Unit*& unit) {
	selectStrategy();
	strategy->applyEffect(unit);
}

void NeutralObject::removeEffect(Unit*& unit) {
	selectStrategy();
	strategy->removeEffect(unit);
}