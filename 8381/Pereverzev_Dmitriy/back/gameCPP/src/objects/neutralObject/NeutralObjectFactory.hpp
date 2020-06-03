#ifndef NeutralObjectFactory_hpp
#define NeutralObjectFactory_hpp

#include <stdio.h>
#include "../../TypeСonstants.hpp"
#include "resourceGenerator/ResourceGenerator.hpp"
#include "resourceGenerator/varietyResourceGenerator/farm/Farm.hpp"
#include "resourceGenerator/varietyResourceGenerator/goldMine/GoldMine.hpp"
#include "resourceGenerator/varietyResourceGenerator/sawmill/Sawmill.hpp"

class NeutralObjectFactory
{
public:
    ResourceGenerator *createResourceGenerator(unsigned int ResourceGeneratorType,std::string ID);
};

#endif /* NeutralObjectFactory_hpp */