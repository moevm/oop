#ifndef NOWEAPON_H
#define NOWEAPON_H

#include "weapon.h"


class NoWeapon : public Weapon
{
public:
    explicit NoWeapon();
    virtual ~NoWeapon() = default;

    NoWeapon(const NoWeapon& weapon);
    NoWeapon(NoWeapon&& armor) = delete;
    NoWeapon& operator=(const NoWeapon& weapon);
    NoWeapon& operator=(NoWeapon&& weapon) = delete;

    virtual size_t getDamage() const override;

    virtual size_t getRadiusAttack() const override;

    virtual size_t getDistanceAttack() const override;

    virtual std::unique_ptr<Weapon> clone() override;
};

#endif // NOWEAPON_H
