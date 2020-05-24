#ifndef weapon_hpp
#define weapon_hpp

#include <stdio.h>
#include <iostream>

constexpr size_t SWORD_SPEAR_DAMAGE = 10;
constexpr size_t ARROW_DAMAGE = 7;
constexpr size_t BALLISTIC_DAMAGE = 15;
constexpr size_t DRAGON_FIRE_DAMAGE = 20;
constexpr size_t VAMPIRE_DAMAGE = 15;
constexpr size_t NO_DAMAGE = 0;

constexpr size_t SHORT_RANGE_DISTANCE = 1;
constexpr size_t LONG_RANGE_DISTANCE = 4;
constexpr size_t DYNAMIC_RANGE_DISTANCE = 6;
constexpr size_t NO_DISTANCE = 0;

constexpr size_t SWORD_SPEAR_RADIUS = 1;
constexpr size_t ARROW_RADIUS = 1;
constexpr size_t BALLISTIC_RADIUS = 4;
constexpr size_t DRAGON_FIRE_RADIUS = 5;
constexpr size_t VAMPIRE_RADIUS = 2;
constexpr size_t NO_RADIUS = 0;


class Weapon
{
public:
    explicit Weapon() = default;
    virtual ~Weapon() = default;

    virtual size_t getDamage() const = 0;
    virtual size_t getRadiusAttack() const = 0;
    virtual size_t getDistanceAttack() const = 0;
    virtual std::string getWeaponttype() const = 0;
    virtual void getWeaponInfo();
    
    virtual std::unique_ptr<Weapon> clone() = 0;
    
protected:
    void doCopy(const Weapon& weapon);

protected:
    std::string weaponType;
    size_t damage;
    size_t radius;
    size_t distance;
};

#endif /* weapon_hpp */
