#include "shooter.h"

Shooter::Shooter(int health, int damage, int armor, int speed, char firingRange) :
    Unit(health, damage, armor, speed), firingRange(firingRange)
{
    setTypeOfAttack('s');
    //qDebug() << "Shooter";
}
