#ifndef NOWEAPONFABRIC_H
#define NOWEAPONFABRIC_H

#include "weaponfactory.h"

#include "Atributes/Weapon/noweapon.h"


class NoWeaponFactory : public WeaponFactory
{
public:
    virtual std::shared_ptr<Weapon> createWeapon() const override;
};

#endif // NOWEAPONFABRIC_H
