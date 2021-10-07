#include "infantry.h"

Infantry::Infantry(int health, int damage, int armor, int speed) :
    Unit(health, damage, armor, speed)
{
    setTypeOfAttack('m');
    //qDebug() << "Infantry ";
}
