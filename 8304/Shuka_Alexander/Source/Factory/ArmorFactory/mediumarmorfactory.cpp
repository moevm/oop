#include "mediumarmorfactory.h"


std::unique_ptr<Armor> MediumArmorFactory::createArmor()
{
    std::unique_ptr<Armor> armor(new MediumArmor);

    return armor;
}
