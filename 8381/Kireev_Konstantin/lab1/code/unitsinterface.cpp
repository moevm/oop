#include <unitsinterface.h>

bool UnitInterface::isMove() const
{
    return true;
}

int UnitInterface::getHealth() const
{
    return health;
}
void UnitInterface::setHealth(int healthNewValue)
{
    health = healthNewValue;
}

int UnitInterface::getArmor() const
{
    return armor;
}
void UnitInterface::setArmor(int armorNewValue)
{
    armor = armorNewValue;
}

int UnitInterface::getDamage() const
{
    return damage;
}
void UnitInterface::setDamage(int damageNewValue)
{
    damage = damageNewValue;
}

void UnitInterface::setAllAttribues(int health, int armor, int damage)
{
    this->health = health;
    this->armor = armor;
    this->damage = damage;
}
