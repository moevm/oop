#ifndef SWORD_H
#define SWORD_H

#include "weapon.h"


class Sword : public Weapon
{
public:
    explicit Sword();
    virtual ~Sword() = default;

    Sword(const Sword& weapon);
    Sword(Sword&& armor) = delete;
    Sword& operator=(const Sword& weapon);
    Sword& operator=(Sword&& weapon) = delete;

    virtual size_t getDamage() const override;

    virtual size_t getRadiusAttack() const override;

    virtual size_t getDistanceAttack() const override;

    virtual std::unique_ptr<Weapon> clone() override;
};

#endif // SWORD_H
