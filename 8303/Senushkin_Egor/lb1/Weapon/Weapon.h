//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_WEAPON_H
#define OOP_LB1__2_WEAPON_H

enum class WeaponType{

    MAGIC,
    PHYSIC,
    RANGE

};

class Weapon {
protected:
    WeaponType type;
    int damage;
public:
    Weapon() = default;
};

#endif //OOP_LB1__2_WEAPON_H
