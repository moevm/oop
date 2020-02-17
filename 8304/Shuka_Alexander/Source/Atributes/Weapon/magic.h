#ifndef MAGIC_H
#define MAGIC_H

#include "weapon.h"


class Magic : public Weapon
{
public:
    explicit Magic();
    virtual ~Magic() = default;

    Magic(const Magic& weapon);
    Magic(Magic&& armor) = delete;
    Magic& operator=(const Magic& weapon);
    Magic& operator=(Magic&& weapon) = delete;

    virtual size_t getDamage() const override;

    virtual size_t getRadiusAttack() const override;

    virtual size_t getDistanceAttack() const override;

    virtual std::unique_ptr<Weapon> clone() override;
};

#endif // MAGIC_H
