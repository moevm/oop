#ifndef WEAPONFABRIC_H
#define WEAPONFABRIC_H

#include <memory>

#include "Atributes/Weapon/weapon.h"


class WeaponFactory
{
public:
    virtual ~WeaponFactory() = default;

    virtual std::shared_ptr<Weapon> createWeapon() const = 0;
};

#endif // WEAPONFABRIC_H
