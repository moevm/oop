#include "melee_unit.h"

Knight::Knight() {
	type = unitType::Knight;
	name = 'K';
	hp.change(30);
	armor.change(40);
	damage.change(20);
}

Rogue::Rogue() {
	type = unitType::Rogue;
	name = 'R';
	hp.change(30);
	armor.change(20);
	damage.change(40);
}