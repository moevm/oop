#ifndef WEAPONFABRIC_H
#define WEAPONFABRIC_H

#include <memory>

#include "Atributes/Weapon/weapon.h"


class WeaponFactory
{
public:
    explicit WeaponFactory() = default;
    virtual ~WeaponFactory() = default;

    virtual std::unique_ptr<Weapon> createWeapon() = 0;
};

#endif // WEAPONFABRIC_H
