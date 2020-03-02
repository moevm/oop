#ifndef arrowweaponfactory_hpp
#define arrowweaponfactory_hpp

#include "weaponfactory.hpp"

#include <stdio.h>

class ArrowWeaponFactory : public WeaponFactory
{
public:
    explicit ArrowWeaponFactory() = default;
    virtual ~ArrowWeaponFactory() = default;

    virtual std::unique_ptr<Weapon> createWeapon() override;
};


#endif /* arrowweaponfactory_hpp */
