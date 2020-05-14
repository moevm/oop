#ifndef vampireteethweaponfactory_hpp
#define vampireteethweaponfactory_hpp

#include "weaponfactory.hpp"

#include <stdio.h>

class VampireTeethWeaponFactory : public WeaponFactory
{
public:
    explicit VampireTeethWeaponFactory() = default;
    virtual ~VampireTeethWeaponFactory() = default;

    virtual std::unique_ptr<Weapon> createWeapon() override;
};


#endif /* VampireTeethweaponfactory_hpp */
