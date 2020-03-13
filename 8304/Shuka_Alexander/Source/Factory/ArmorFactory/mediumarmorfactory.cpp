#include "mediumarmorfactory.h"


std::shared_ptr<Armor> MediumArmorFactory::createArmor() const
{
    return std::make_shared<MediumArmor>();
}
