#ifndef spearweaponfactory_hpp
#define spearweaponfactory_hpp

#include "weaponfactory.hpp"

#include <stdio.h>

class SpearWeaponFactory : public WeaponFactory
{
public:
    explicit SpearWeaponFactory() = default;
    virtual ~SpearWeaponFactory() = default;

    virtual std::unique_ptr<Weapon> createWeapon() override;
};

#endif /* spearweaponfactory_hpp */
