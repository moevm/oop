#ifndef spearweapon_hpp
#define spearweapon_hpp

#include "weapon.hpp"

#include <stdio.h>

class SpearWeapon : public Weapon
{
public:
    explicit SpearWeapon();
    virtual ~SpearWeapon() = default;

    SpearWeapon(const SpearWeapon& weapon);
    SpearWeapon(SpearWeapon&& armor) = delete;
    SpearWeapon& operator=(const SpearWeapon& weapon);
    SpearWeapon& operator=(SpearWeapon&& weapon) = delete;

    virtual size_t getDamage() const override;
    virtual size_t getRadiusAttack() const override;
    virtual size_t getDistanceAttack() const override;
    virtual std::string getWeaponttype() const override;

    virtual std::unique_ptr<Weapon> clone() override;
};

#endif /* spearweapon_hpp */
