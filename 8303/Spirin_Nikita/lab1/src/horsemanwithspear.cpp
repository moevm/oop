#include "horsemanwithspear.h"


HorsemanWithSpear::HorsemanWithSpear(int health, int damage, int armor, int speed) :
    Horseman(health, damage, armor, speed)
{
    //qDebug() << "HorsemanWithSpear";
}

char HorsemanWithSpear::getID() const
{
    return '6';
}
