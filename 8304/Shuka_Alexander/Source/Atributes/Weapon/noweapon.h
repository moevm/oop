#ifndef NOWEAPON_H
#define NOWEAPON_H

#include "weapon.h"


class NoWeapon : public Weapon
{
public:
    explicit NoWeapon();

    NoWeapon(const NoWeapon& weapon);
    NoWeapon& operator=(const NoWeapon& weapon);

    virtual size_t getDamage() const override;
    virtual size_t getRadiusAttack() const override;
    virtual size_t getDistanceAttack() const override;

    virtual std::shared_ptr<Weapon> clone() const override;
};

#endif // NOWEAPON_H
