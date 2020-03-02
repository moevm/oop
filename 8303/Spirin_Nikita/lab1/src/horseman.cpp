#include "horseman.h"

Horseman::Horseman(int health, int damage, int armor, int speed) :
    Unit(health, damage, armor, speed)
{
    setTypeOfAttack('m');
    //qDebug() << "Horseman";
}
