#include "unit.h"

Unit::Unit()
{

}

void Unit::deapth()
{
    this->notify();
}

void Unit::getDamage(int numb)
{
    this->attributes->health -= numb;
    std::cout << "Unit is damaged\n";
    if (this->attributes->health <= 0){
        this->deapth();
        std::cout << "Unit died\n";
    }
}
