#include "range_unit.h"

Archer::Archer() {
	type = unitType::Archer;
	name = 'A';
	hp.change(30);
	armor.change(20);
	damage.change(40);
}

Mage::Mage() {
	type = unitType::Mage;
	name = 'M';
	hp.change(40);
	damage.change(40);
}