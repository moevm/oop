#ifndef vampireteethweapon_hpp
#define vampireteethweapon_hpp

#include "weapon.hpp"

#include <stdio.h>

class VampireTeethWeapon : public Weapon
{
public:
    explicit VampireTeethWeapon();
    virtual ~VampireTeethWeapon() = default;

    VampireTeethWeapon(const VampireTeethWeapon& weapon);
    VampireTeethWeapon(VampireTeethWeapon&& armor) = delete;
    VampireTeethWeapon& operator=(const VampireTeethWeapon& weapon);
    VampireTeethWeapon& operator=(VampireTeethWeapon&& weapon) = delete;

    virtual size_t getDamage() const override;
    virtual size_t getRadiusAttack() const override;
    virtual size_t getDistanceAttack() const override;
    virtual std::string getWeaponttype() const override;

    virtual std::unique_ptr<Weapon> clone() override;
};

#endif /* VampireTeethWeapon_hpp */
