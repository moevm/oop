#ifndef MAGICWEAPONFABRIC_H
#define MAGICWEAPONFABRIC_H

#include "weaponfactory.h"

#include "Atributes/Weapon/magic.h"


class MagicWeaponFactory : public WeaponFactory
{
public:
    virtual std::shared_ptr<Weapon> createWeapon() const override;
};

#endif // MAGICWEAPONFABRIC_H
