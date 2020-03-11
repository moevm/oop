#ifndef MAGICWEAPONFABRIC_H
#define MAGICWEAPONFABRIC_H

#include "weaponfactory.h"

#include "Atributes/Weapon/magic.h"


class MagicWeaponFactory : public WeaponFactory
{
public:
    explicit MagicWeaponFactory() = default;
    virtual ~MagicWeaponFactory() = default;

    virtual std::unique_ptr<Weapon> createWeapon() override;
};

#endif // MAGICWEAPONFABRIC_H
