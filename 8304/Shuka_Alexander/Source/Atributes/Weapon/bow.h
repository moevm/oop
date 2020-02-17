#ifndef BOW_H
#define BOW_H

#include "weapon.h"


class Bow : public Weapon
{
public:
    explicit Bow();
    virtual ~Bow() = default;

    Bow(const Bow& weapon);
    Bow(Bow&& armor) = delete;
    Bow& operator=(const Bow& weapon);
    Bow& operator=(Bow&& weapon) = delete;

    virtual size_t getDamage() const override;

    virtual size_t getRadiusAttack() const override;

    virtual size_t getDistanceAttack() const override;

    virtual std::unique_ptr<Weapon> clone() override;
};

#endif // BOW_H
