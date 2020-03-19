#ifndef SWORD_H
#define SWORD_H

#include "weapon.h"


class Sword : public Weapon
{
public:
    explicit Sword();

    Sword(const Sword& weapon);
    Sword& operator=(const Sword& weapon);

    virtual size_t getDamage() const override;
    virtual size_t getRadiusAttack() const override;
    virtual size_t getDistanceAttack() const override;

    virtual std::shared_ptr<Weapon> clone() const override;
};

#endif // SWORD_H
