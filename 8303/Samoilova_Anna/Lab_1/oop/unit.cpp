#include "unit.h"

Unit::Unit()
{

}

unsigned int Unit::get_step() const{
    return step;
}

unsigned int Unit::get_attack() const{
    return attack;
}

unsigned int Unit::get_health() const{
    return health;
}

bool Unit::get_is_child() const{
    return child;
}

