#ifndef SWORDWEAPONFABRIC_H
#define SWORDWEAPONFABRIC_H

#include "weaponfactory.h"

#include "Atributes/Weapon/sword.h"


class SwordWeaponFactory : public WeaponFactory
{
public:
    explicit SwordWeaponFactory() = default;
    virtual ~SwordWeaponFactory() = default;

    virtual std::unique_ptr<Weapon> createWeapon() override;
};

#endif // SWORDWEAPONFABRIC_H
