#include "archer.h"

Archer::Archer(int health, int damage, int armor, int speed, int firingRange) :
    Shooter(health, damage, armor, speed, firingRange)
{
    //this->Unit::createUnit(health, damage, armor, speed);
    //qDebug() << "Archer";
}

char Archer::getID() const
{
    return '3';
}
