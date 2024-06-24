//
// Created by Глебушунок on 15.03.2020.
//

#ifndef OOP_LAB1_SNOW_H
#define OOP_LAB1_SNOW_H

#include "Landscape.h"

class Snow: public Landscape {

public:

    void print(std::ostream &stream, GameObject &object) const override{

        stream << "[" << object << "]";

    }

    void print(std::ostream &stream) const override{

        stream << "[" << "." << "]";

    }

    int getDamageFactor(WeaponType type) override {
        switch (type){

            case WeaponType::PHYSIC :
            case WeaponType::FAR:
                return 1;
            case WeaponType::MAGIC:
                return 100;
        }
    }

    int getAbsorptionFactor(ArmorType type) override {
        switch (type) {

            case ArmorType::HEAVY:
            case ArmorType::LIGHT:
            case ArmorType::MEDIUM:
                return 1;
        }
    }

};

#endif //OOP_LAB1_SNOW_H
