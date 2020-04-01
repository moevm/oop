#ifndef dragonfireweapon_hpp
#define dragonfireweapon_hpp

#include "weapon.hpp"

#include <stdio.h>

class DragonFireWeapon : public Weapon
{
public:
    explicit DragonFireWeapon();
    virtual ~DragonFireWeapon() = default;

    DragonFireWeapon(const DragonFireWeapon& weapon);
    DragonFireWeapon(DragonFireWeapon&& armor) = delete;
    DragonFireWeapon& operator=(const DragonFireWeapon& weapon);
    DragonFireWeapon& operator=(DragonFireWeapon&& weapon) = delete;

    virtual size_t getDamage() const override;
    virtual size_t getRadiusAttack() const override;
    virtual size_t getDistanceAttack() const override;
    virtual std::string getWeaponttype() const override;

    virtual std::unique_ptr<Weapon> clone() override;
};

#endif /* dragonfireweapon_hpp */
