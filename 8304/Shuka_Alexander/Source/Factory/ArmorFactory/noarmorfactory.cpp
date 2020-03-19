#include "noarmorfactory.h"


std::shared_ptr<Armor> NoArmorFactory::createArmor() const
{
    return std::make_shared<NoArmor>();
}
