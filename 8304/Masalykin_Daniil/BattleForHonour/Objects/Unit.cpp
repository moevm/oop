#include "Unit.h"

Unit::Unit(const Unit &other):
        GameObject(ObjectType::UNIT),
        armor(other.armor),
        weapon(other.weapon),
        health(other.health) {}

void Unit::addObserver(UnitObserver *observer) {

    Log::log << "[#Unit] observer added" << Log::logend;
    observers.push_back(observer);

}

void Unit::move(Point point) {

    for (auto elem: observers){
        elem->onUnitMove(this, point);
    }
    Log::log << "[#Unit] moves" << Log::logend;

}

void Unit::attack(Unit &other) {

    for (auto elem: observers){
        elem->onUnitAttack(this, &other);
    }
    Log::log << "[#Unit] attacks" << Log::logend;

}

void Unit::damage(int damage) {

    for (auto elem: observers) {
        elem->onUnitDamaged(this);
    }

    if (damage < 0)
        damage = 0;
    health -= damage;

    if (health <= 0){
        for (auto elem: observers) {
            elem->onUnitDestroy(this);
        }
    }
    Log::log << "[#Unit] damaged by " << damage << " points" << Log::logend;
}

void Unit::heal(int hp) {
    for (auto elem: observers) {
        elem->onUnitHeal(this);
    }
    health += hp;
    Log::log << "[#Unit] healed by " << hp << " points \n" << Log::logend;
}

Unit &Unit::operator=(const Unit &unit) {

    armor = unit.armor;
    weapon = unit.weapon;
    health = unit.health;
    return *this;
}

Unit &Unit::operator<<(NeutralObject *neutralObject) {
    neutralObject->toEffect(*this);
    return *this;
}

Unit::Unit(UnitType unitType, Armor &armor, Weapon &weapon, int health):
        GameObject(ObjectType::UNIT),
        unitType(unitType),
        armor(armor),
        weapon(weapon),
        health(health)
{}

int Unit::getHealth() const {
    return health;
}

void Unit::print(std::ostream &stream) const {
    switch(unitType){
        case UnitType::DRUID:
            stream << "D";
            break;
        case UnitType::ARCHER:
            stream << "A";
            break;
        case UnitType::INFANTRY:
            stream << "I";
            break;
    }
}