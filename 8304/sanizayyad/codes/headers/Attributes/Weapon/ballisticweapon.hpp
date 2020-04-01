#ifndef ballisticweapon_hpp
#define ballisticweapon_hpp

#include "weapon.hpp"

#include <stdio.h>

class BallisticWeapon : public Weapon
{
public:
    explicit BallisticWeapon();
    virtual ~BallisticWeapon() = default;

    BallisticWeapon(const BallisticWeapon& weapon);
    BallisticWeapon(BallisticWeapon&& armor) = delete;
    BallisticWeapon& operator=(const BallisticWeapon& weapon);
    BallisticWeapon& operator=(BallisticWeapon&& weapon) = delete;

    virtual size_t getDamage() const override;
    virtual size_t getRadiusAttack() const override;
    virtual size_t getDistanceAttack() const override;
    virtual std::string getWeaponttype() const override;

    virtual std::unique_ptr<Weapon> clone() override;
};

#endif /* ballisticweapon_hpp */
