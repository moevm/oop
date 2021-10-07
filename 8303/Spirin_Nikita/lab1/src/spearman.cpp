#include "spearman.h"

Spearman::Spearman(int health, int damage, int armor, int speed) :
    Infantry(health, damage, armor, speed)
{
    //qDebug() << "Spearman";
}


char Spearman::getID() const
{
    return '2';
}
