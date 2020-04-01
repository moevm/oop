#ifndef mediumarmorfactory_hpp
#define mediumarmorfactory_hpp

#include "armorfactory.hpp"

#include <stdio.h>

class MediumArmorFactory : public ArmorFactory
{
public:
    explicit MediumArmorFactory() = default;
    virtual ~MediumArmorFactory() = default;

    virtual std::unique_ptr<Armor> createArmor() override;
};

#endif /* mediumarmorfactory_hpp */
