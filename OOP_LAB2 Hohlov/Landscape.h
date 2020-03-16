//
// Created by Глебушунок on 15.03.2020.
//

#ifndef OOP_LAB1_LANDSCAPE_H
#define OOP_LAB1_LANDSCAPE_H
#include "Weapon.h"
#include "Armor.h"
#include "GameObject.h"

class Landscape {

public:

    virtual void print(std::ostream &stream, GameObject &object) const = 0;
    virtual void print(std::ostream &stream) const = 0;

    virtual int getDamageFactor(WeaponType type) = 0;
    virtual int getAbsorptionFactor(ArmorType type) = 0;

    friend std::ostream& operator<<(std::ostream &stream, const Landscape &landscape){
        landscape.print(stream);
        return stream;
    }

};


#endif //OOP_LAB1_LANDSCAPE_H
