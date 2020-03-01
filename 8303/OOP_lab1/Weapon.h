
#ifndef OOP_LAB1_WEAPON_H
#define OOP_LAB1_WEAPON_H
enum class WeaponType{

    MAGIC,
    PHYSIC,
    FAR

};

class Weapon {

protected:

    WeaponType type;
    int damage;

};
#endif //OOP_LAB1_WEAPON_H
