#ifndef MAGIC_H
#define MAGIC_H

#include "weapon.h"


class Magic : public Weapon
{
public:
    explicit Magic();

    Magic(const Magic& weapon);
    Magic& operator=(const Magic& weapon);

    virtual size_t getDamage() const override;
    virtual size_t getDistanceAttack() const override;

    virtual std::shared_ptr<Weapon> clone() const override;
};

#endif // MAGIC_H
