#include "swordsman.h"

Swordsman::Swordsman(int health, int damage, int armor, int speed):
    Infantry(health, damage, armor, speed)
{
    //qDebug() << "Swordsman";
}

char Swordsman::getID() const
{
    return '1';
}
