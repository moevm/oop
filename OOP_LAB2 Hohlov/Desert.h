//
// Created by Глебушунок on 15.03.2020.
//

#ifndef OOP_LAB1_DESERT_H
#define OOP_LAB1_DESERT_H

#include "Landscape.h"

class Desert: public Landscape {

public:

    void print(std::ostream &stream, GameObject &object) const override{

        stream << "(" << object << ")";

    }

    void print(std::ostream &stream) const override{

        stream << "(" << "." << ")";

    }

    int getDamageFactor(WeaponType type) override {
        switch (type){

            case WeaponType::PHYSIC :
                return 1;
            case WeaponType::MAGIC:
            case WeaponType::FAR:
                return 3;
        }
    }

    int getAbsorptionFactor(ArmorType type) override {
        switch (type){
            case ArmorType::HEAVY:
                return 1;
            case ArmorType::LIGHT:
                return 5;
            case ArmorType::MEDIUM:
                return 2;
        }
    }

};

#endif //OOP_LAB1_DESERT_H
