#ifndef lightarmorfactory_hpp
#define lightarmorfactory_hpp

#include "armorfactory.hpp"

#include <stdio.h>

class LightArmorFactory : public ArmorFactory
{
public:
    explicit LightArmorFactory() = default;
    virtual ~LightArmorFactory() = default;

    virtual std::unique_ptr<Armor> createArmor() override;
};


#endif /* lightarmorfactory_hpp */
