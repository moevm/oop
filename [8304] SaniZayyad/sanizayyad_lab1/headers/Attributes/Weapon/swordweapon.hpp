#ifndef swordweapon_hpp
#define swordweapon_hpp

#include "weapon.hpp"

#include <stdio.h>

class SwordWeapon : public Weapon
{
public:
    explicit SwordWeapon();
    virtual ~SwordWeapon() = default;

    SwordWeapon(const SwordWeapon& weapon);
    SwordWeapon(SwordWeapon&& armor) = delete;
    SwordWeapon& operator=(const SwordWeapon& weapon);
    SwordWeapon& operator=(SwordWeapon&& weapon) = delete;

    virtual size_t getDamage() const override;
    virtual size_t getRadiusAttack() const override;
    virtual size_t getDistanceAttack() const override;
    virtual std::string getWeaponttype() const override;

    virtual std::unique_ptr<Weapon> clone() override;
};


#endif /* swordweapon_hpp */
