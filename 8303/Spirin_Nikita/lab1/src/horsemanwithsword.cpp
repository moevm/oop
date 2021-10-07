#include "horsemanwithsword.h"

HorsemanWithSword::HorsemanWithSword(int health, int damage, int armor, int speed) :
    Horseman(health, damage, armor, speed)
{
    //qDebug() << "HorsemanWithSword";
}

char HorsemanWithSword::getID() const
{
    return '5';
}
