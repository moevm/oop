#ifndef WEAPON_H
#define WEAPON_H

#include <cstddef>
#include <memory>


constexpr size_t SWORD_DMG = 10;
constexpr size_t BOW_DMG = 20;
constexpr size_t MAGIC_DMG = 15;
constexpr size_t NO_DMG = 0;

constexpr size_t MELEE_DISTANCE = 1;
constexpr size_t RANGE_DISTANCE = 4;
constexpr size_t NO_DISTANCE = 0;


class Weapon
{
public:
    virtual ~Weapon() = default;

    virtual size_t getDamage() const = 0;
    virtual size_t getDistanceAttack() const = 0;

    virtual std::shared_ptr<Weapon> clone() const = 0;
    
protected:
    void doCopy(const Weapon& weapon);

protected:
    size_t damage;
    size_t distance;
};

#endif // WEAPON_H
