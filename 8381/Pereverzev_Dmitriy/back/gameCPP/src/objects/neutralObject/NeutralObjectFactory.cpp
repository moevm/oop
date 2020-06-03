#include "NeutralObjectFactory.hpp"

ResourceGenerator *NeutralObjectFactory::createResourceGenerator(unsigned int ResourceGeneratorType, std::string ID)
{
    if (ResourceGeneratorType == GEN_GOLD)
        return new GoldMine(ID);
    if (ResourceGeneratorType == GEN_FARM)
        return new Farm(ID);
    if (ResourceGeneratorType == GEN_SAWMILL)
        return new Sawmill(ID);
}
