#include "CombatObjectType.hpp"

CombatObjectType::CombatObjectType(double health, double damage, double armor)
{
    this->maxHealth = health;
    this->damage = damage;
    this->armor = armor;
}

double CombatObjectType::getMaxHealth() const { return maxHealth; }

double CombatObjectType::getDamage() const { return damage; }

double CombatObjectType::getArmor() const { return armor; }

bool CombatObjectType::dataСomparison(double health, double damage, double armor)
{
    return (this->maxHealth == health && this->damage == damage && this->armor == armor);
}
