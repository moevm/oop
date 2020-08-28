#include "cavalry.hpp"

int Cavalry::getSpeed () {
    return 3;
}

MovingType Cavalry::getMovingType () {
    return HORSE;
}

void Cavalry::takeDamage (DamageType damageType, int value) {
    if(damageType == PRICKING) {
        Unit::takeDamage(damageType, value * 2);
    } else {
        Unit::takeDamage(damageType, value);
    }
}
