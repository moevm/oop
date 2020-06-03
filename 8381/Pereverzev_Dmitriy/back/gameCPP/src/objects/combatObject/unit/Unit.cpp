
#include "Unit.hpp"

Unit::~Unit()
{
    
}
void Unit::operator+(Object *object) {}

bool Unit::isMoveable() { return true; }



/*
void Unit::setHealth(double health)
{
    if (health < 0)
        death();
    else
    {
        
        fireEvent("object updated");
    }

    this->health = health;
}

double Unit::getHealth() const { return health; }
double Unit::getMaxHealth() const { return type->getMaxHealth(); }
double Unit::getDamage() const { return type->getDamage(); }
double Unit::getArmor() const { return type->getArmor(); } */

void Unit::death() { fireEvent("object death"); }







v8::Local<v8::Object> Unit::getFullInfo()
{
    v8::Local<v8::Object> info = CombatObject::getFullInfo();

    return info;
}
void Unit::eventHandler(Event *event){};