#include "unit.h"

using namespace unit;


Unit::Unit(const Point2D& point, std::shared_ptr<Mediator> mediator) :
    position(point), mediator(mediator)
{

}


Unit::Unit(const Unit& unit) : position(unit.position)
{

}


int Unit::getHealthPoints() const
{
    return healthPoints;
}


const Point2D& Unit::getPosition() const
{
    return position;
}


const std::shared_ptr<Armor> Unit::getArmor() const
{
    return armor;
}


const std::shared_ptr<Weapon> Unit::getWeapon() const
{
    return weapon;
}


void Unit::setWeapon(std::shared_ptr<Weapon> weapon)
{
    if (weapon) {
        this->weapon = std::move(weapon);
    }
}


void Unit::setArmor(std::shared_ptr<Armor> armor)
{
    if (armor) {
        this->armor = std::move(armor);
    }
}


void Unit::toHurt(int damage)
{
    healthPoints -= damage;
}


void Unit::setMediator(std::shared_ptr<Mediator> mediator)
{
    this->mediator = mediator;
}


void Unit::doCopy(const Unit& unit)
{
    if (unit.armor) {
        this->armor = unit.armor->clone();
    }

    if (unit.weapon) {
        this->weapon = unit.weapon->clone();
    }

    this->position = unit.position;
    this->healthPoints = unit.healthPoints;
}
