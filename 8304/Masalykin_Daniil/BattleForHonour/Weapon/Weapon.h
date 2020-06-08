#ifndef BATTLEFORHONOUR_WEAPON_H
#define BATTLEFORHONOUR_WEAPON_H


#include <ostream>
#include "WeaponType.h"


class Weapon {

protected:

    WeaponType type;
    int damage;

public:

    int getDamage() const {
        return damage;
    }
    WeaponType getType() const {
        return type;
    }

    bool operator==(const Weapon &other){
        return type == other.type && damage == other.damage;
    }

    Weapon& operator=(const Weapon& other){
        if (this == &other) return *this;
        type = other.type;
        damage = other.damage;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Weapon &weapon){
        stream << "Weapon = " << "Damage: " << weapon.damage;
        return stream;
    }

};

class Sword: public Weapon{
public:
    Sword(){
        damage = 10;
        type = WeaponType::PHYSIC;
    }
};

class StarFall: public Weapon{
public:
    StarFall(){
        damage = 50;
        type = WeaponType::MAGIC;
    }
};

class Spear: public Weapon{
public:
    Spear(){
        damage = 20;
        type = WeaponType::PHYSIC;
    }
};

class Bow: public Weapon{
public:
    Bow(){
        damage = 10;
        type = WeaponType::DISTANCE;
    }
};

class AbolishMagic: public Weapon{

public:
    AbolishMagic(){
        damage = 20;
        type = WeaponType::MAGIC;
    }
};

#endif //BATTLEFORHONOUR_WEAPON_H
