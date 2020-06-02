#include "Unit.h"

Unit::Unit(Unit *other) {

    armor = other->armor;
    weapon = other->weapon;
    health = other->health;

}
