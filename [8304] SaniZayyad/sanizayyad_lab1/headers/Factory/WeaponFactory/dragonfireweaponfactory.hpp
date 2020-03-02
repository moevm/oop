#ifndef dragonfireweaponfactory_hpp
#define dragonfireweaponfactory_hpp


#include "weaponfactory.hpp"

#include <stdio.h>

class DragonFireWeaponFactory : public WeaponFactory
{
public:
    explicit DragonFireWeaponFactory() = default;
    virtual ~DragonFireWeaponFactory() = default;

    virtual std::unique_ptr<Weapon> createWeapon() override;
};


#endif /* dragonfireweaponfactory_hpp */
