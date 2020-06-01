#include "UnitAttributes.h"


void UnitAttributes::setAll(int hp, int ap, int dmg, int r) {
	healPoints = hp;
	armorPoints = ap;
	damage = dmg;
	range = r;
}

int UnitAttributes::getHealPoints() const {
	return healPoints;
}
int UnitAttributes::getArmorPoints() const {
	return armorPoints;
}
int UnitAttributes::getDamage() const {
	return damage;
}
int UnitAttributes::getRange() const {
	return range;
}

void UnitAttributes::setHealPoints(int hp) {
	healPoints = hp;
}
void UnitAttributes::setArmorPoints(int ap) {
	armorPoints = ap;
}
void UnitAttributes::setDamage(int dmg) {
	damage = dmg;
}
void UnitAttributes::setRange(int r) {
	range = r;
}