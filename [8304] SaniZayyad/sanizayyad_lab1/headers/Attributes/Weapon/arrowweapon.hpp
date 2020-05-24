#ifndef arrowweapon_hpp
#define arrowweapon_hpp

#include "weapon.hpp"

#include <stdio.h>

class ArrowWeapon : public Weapon
{
public:
    explicit ArrowWeapon();
    virtual ~ArrowWeapon() = default;

    ArrowWeapon(const ArrowWeapon& weapon);
    ArrowWeapon(ArrowWeapon&& armor) = delete;
    ArrowWeapon& operator=(const ArrowWeapon& weapon);
    ArrowWeapon& operator=(ArrowWeapon&& weapon) = delete;

    virtual size_t getDamage() const override;
    virtual size_t getRadiusAttack() const override;
    virtual size_t getDistanceAttack() const override;
    virtual std::string getWeaponttype() const override;

    virtual std::unique_ptr<Weapon> clone() override;
};

#endif /* arrowweapon_hpp */
