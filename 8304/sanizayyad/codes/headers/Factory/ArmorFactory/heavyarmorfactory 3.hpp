#ifndef heavyarmorfactory_hpp
#define heavyarmorfactory_hpp

#include "armorfactory.hpp"

#include <stdio.h>

class HeavyArmorFactory : public ArmorFactory
{
public:
    explicit HeavyArmorFactory() = default;
    virtual ~HeavyArmorFactory() = default;

    virtual std::unique_ptr<Armor> createArmor() override;
};

#endif /* heavyarmorfactory_hpp */
