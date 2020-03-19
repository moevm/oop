#ifndef SWORDWEAPONFABRIC_H
#define SWORDWEAPONFABRIC_H

#include "weaponfactory.h"

#include "Atributes/Weapon/sword.h"


class SwordWeaponFactory : public WeaponFactory
{
public:
    virtual std::shared_ptr<Weapon> createWeapon() const override;
};

#endif // SWORDWEAPONFABRIC_H
