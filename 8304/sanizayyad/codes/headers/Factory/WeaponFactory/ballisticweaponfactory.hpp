#ifndef ballisticweaponfactory_hpp
#define ballisticweaponfactory_hpp

#include "weaponfactory.hpp"

#include <stdio.h>

class BallisticWeaponFactory : public WeaponFactory
{
public:
    explicit BallisticWeaponFactory() = default;
    virtual ~BallisticWeaponFactory() = default;

    virtual std::unique_ptr<Weapon> createWeapon() override;
};


#endif /* ballisticweaponfactory_hpp */
