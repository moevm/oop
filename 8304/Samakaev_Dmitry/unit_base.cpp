#include "unit_base.h"


void Unit::on_damage_taken(size_t damage_to_take)
{
	if (damage_to_take <= armor.get()) {
		armor.change(armor.get() - damage_to_take);
	}
	else {
		if (damage_to_take < hp.get()) {
			hp.change(hp.get() - damage_to_take + armor.get());
		}
		else {
			hp.change(0);
			play_dead();
		}
	}
}

void Unit::play_dead()
{

	std::cout << name << " is dead now\n";
}
