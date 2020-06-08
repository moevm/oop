#ifndef BATTLEFORHONOUR_TERRAIN_H
#define BATTLEFORHONOUR_TERRAIN_H


#include "../Weapon/Weapon.h"
#include "../Armor/Armor.h"
#include "../Objects/GameObject.h"

class Terrain {

public:

    virtual void print(std::ostream &stream, GameObject &object) const = 0;
    virtual void print(std::ostream &stream) const = 0;

    virtual int getDamageMultiply(WeaponType type) = 0;
    virtual int getAbsorbMultiply(ArmorType type) = 0;

    friend std::ostream& operator<<(std::ostream &stream, const Terrain &terrain){
        terrain.print(stream);
        return stream;
    }

};

class Wasteland: public Terrain {

public:

    void print(std::ostream &stream, GameObject &object) const override{

        stream << "[" << object << "]";

    }

    void print(std::ostream &stream) const override{

        stream << "[" << "#" << "]";

    }

    int getDamageMultiply(WeaponType type) override {
        switch (type){

            case WeaponType::PHYSIC:
                return 0;
            case WeaponType::DISTANCE:
                return 1;
            case WeaponType::MAGIC:
                return 100;
        }
    }

    int getAbsorbMultiply(ArmorType type) override {
        switch (type){
            case ArmorType::MAGIC:
                return 100;
            case ArmorType::HEAVY:
                return 0;
            case ArmorType::LIGHT:
                return 0;
            case ArmorType::MEDIUM:
                return 1;
        }
    }

};

class Swamp: public Terrain {

public:

    void print(std::ostream &stream, GameObject &object) const override{

        stream << "<" << object << ">";

    }

    void print(std::ostream &stream) const override{

        stream << "<" << "#" << ">";

    }

    int getDamageMultiply(WeaponType type) override {
        switch (type){

            case WeaponType::PHYSIC :
                return 1;
            case WeaponType::MAGIC:
                return 2;
            case WeaponType::DISTANCE:
                return 3;
        }
    }

    int getAbsorbMultiply(ArmorType type) override {
        switch (type){

            case ArmorType::MAGIC:
                return 10;
            case ArmorType::HEAVY:
                return 1;
            case ArmorType::LIGHT:
                return 5;
            case ArmorType::MEDIUM:
                return 2;
        }
    }

};

class Desert: public Terrain {

public:

    void print(std::ostream &stream, GameObject &object) const override{

        stream << "{" << object << "}";

    }

    void print(std::ostream &stream) const override{

        stream << "{" << "#" << "}";

    }

    int getDamageMultiply(WeaponType type) override {

        switch (type){
            case WeaponType::PHYSIC :
                return 1;
            case WeaponType::MAGIC:
                return 0;
            case WeaponType::DISTANCE:
                return 3;
        }

    }

    int getAbsorbMultiply(ArmorType type) override {
        switch (type){

            case ArmorType::MAGIC:
                return 1;
            case ArmorType::HEAVY:
                return 2;
            case ArmorType::LIGHT:
                return 3;
            case ArmorType::MEDIUM:
                return 4;
        }
    }

};

class Border: public Terrain {

public:
    void print(std::ostream &stream) const override {
        stream << "+";
    }
};

#endif //BATTLEFORHONOUR_TERRAIN_H
