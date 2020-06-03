#include "UnitTank.hpp"

void UnitTank::underAttack(double damage, double armor)
{
    std::srand((unsigned int)time(nullptr));
    if ((std::rand() % 10) * 0.1 < critChance)
        damage = damage / critAbsorption;
    damage = damage * (1 + (armor - this->type->getArmor()) / 10);
    this->setHealth(this->getHealth() - damage);
}

v8::Local<v8::Object> UnitTank::getFullInfo()
{
    v8::Local<v8::Object> info = Unit::getFullInfo();
    v8::Local<v8::Object> stats;

    GetObjProperty(info, "stats", stats);
    SetObjProperty(stats, "critChance", critChance);
    SetObjProperty(stats, "critAbsorption", critAbsorption);
    SetObjProperty(info, "stats", stats);
    return info;
}
