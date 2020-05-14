#ifndef swordfactory_hpp
#define swordfactory_hpp

#include "weaponfactory.hpp"

#include <stdio.h>

class SwordWeaponFactory : public WeaponFactory
{
public:
    explicit SwordWeaponFactory() = default;
    virtual ~SwordWeaponFactory() = default;

    virtual std::unique_ptr<Weapon> createWeapon() override;
};


#endif /* swordfactory_hpp */
