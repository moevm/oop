#ifndef BATTLEFORHONOUR_ARMORFLYWEIGHT_H
#define BATTLEFORHONOUR_ARMORFLYWEIGHT_H


#include <vector>
#include "Armor.h"

class ArmorFlyweight {

private:

    static ArmorFlyweight *self;
    std::vector<Armor*> armorArr;

public:
    template <typename Type>
    static Type* getFlyweight(){

        if (!self)
            self = new ArmorFlyweight();

        Type typeArmor;
        for (auto *armor: self->armorArr){
            if (typeArmor == *armor){
                return static_cast<Type*>(armor);
            }
        }

        Type *armorPtr = new Type();
        self->armorArr.push_back(armorPtr);
        return armorPtr;
    }
};

ArmorFlyweight *ArmorFlyweight::self = nullptr;


#endif //BATTLEFORHONOUR_ARMORFLYWEIGHT_H
