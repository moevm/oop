
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

public:

    int getDamage() const { return damage; }
    WeaponType getType() const { return type; }

    bool operator==(const Weapon &other){

        return type == other.type && damage == other.damage;

    }

    Weapon& operator=(const Weapon& other){

        if (this == &other) return *this;
        type = other.type;
        damage = other.damage;
        return *this;

    }

};

#endif //OOP_LAB1_WEAPON_H
