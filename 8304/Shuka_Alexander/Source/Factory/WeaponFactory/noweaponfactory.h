#ifndef NOWEAPONFABRIC_H
#define NOWEAPONFABRIC_H

#include "weaponfactory.h"

#include "Atributes/Weapon/noweapon.h"


class NoWeaponFactory : public WeaponFactory
{
public:
    explicit NoWeaponFactory() = default;
    virtual ~NoWeaponFactory() = default;

    virtual std::unique_ptr<Weapon> createWeapon() override;
};

#endif // NOWEAPONFABRIC_H
