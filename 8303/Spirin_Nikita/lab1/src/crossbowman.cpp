#include "crossbowman.h"

Crossbowman::Crossbowman(int health, int damage, int armor, int speed, int firingRange) :
    Shooter(health, damage, armor, speed, firingRange)
{
//    this->Unit::createUnit(health, damage, armor, speed);
    //qDebug() << "Crossbowman";
}

char Crossbowman::getID() const
{
    return '4';
}
