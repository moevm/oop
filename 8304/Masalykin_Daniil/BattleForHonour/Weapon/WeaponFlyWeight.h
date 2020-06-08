#ifndef BATTLEFORHONOUR_WEAPONFLYWEIGHT_H
#define BATTLEFORHONOUR_WEAPONFLYWEIGHT_H


#include <vector>
#include "Weapon.h"

class WeaponFlyweight {

private:

    static WeaponFlyweight *self;
    std::vector<Weapon*> weapons;

public:

    template <typename Type>
    static Type* getFlyWeight(){

        if (!self)
            self = new WeaponFlyweight();

        Type setWeapon;
        for (auto *weapon: self->weapons){

            if (setWeapon == *weapon){
                return static_cast<Type*>(weapon);
            }
        }

        Type *tmp = new Type();
        self->weapons.push_back(tmp);
        return tmp;
    }
};

WeaponFlyweight *WeaponFlyweight::self = nullptr;


#endif //BATTLEFORHONOUR_WEAPONFLYWEIGHT_H
