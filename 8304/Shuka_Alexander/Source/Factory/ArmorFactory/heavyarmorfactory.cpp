#include "heavyarmorfactory.h"


std::unique_ptr<Armor> HeavyArmorFactory::createArmor()
{
    std::unique_ptr<Armor> armor(new HeavyArmor);

    return armor;
}
