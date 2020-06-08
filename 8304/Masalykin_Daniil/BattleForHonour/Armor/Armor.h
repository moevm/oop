#ifndef BATTLEFORHONOUR_ARMOR_H
#define BATTLEFORHONOUR_ARMOR_H

#include <ostream>
#include "ArmorType.h"


class Armor {

protected:

    ArmorType type;
    int absorbation{};

public:

    Armor(){}

    [[nodiscard]] int controlAbsorb() const {
        return this->absorbation;
    }
    ArmorType getArmorType(){
        return type;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Armor &armor){
        stream << "Armor = " << "Damage Absorb: " << armor.absorbation << " ;";
        return stream;
    }

    bool operator==(Armor &other){
        return this->type == other.type && this->absorbation == other.absorbation;
    }

    Armor& operator=(const Armor& tmp){
        if (this == &tmp)
            return *this;
        this->type = tmp.type;
        this->absorbation = tmp.absorbation;
        return *this;
    }
};


class LeatherArmor: public Armor {

public:
    LeatherArmor(){
        type = ArmorType::LIGHT;
        absorbation = 2;
    }
};

class PlateMail: public Armor{

public:
    PlateMail(){
        type = ArmorType::MEDIUM;
        absorbation = 5;
    }

};

class Robe: public Armor{

public:
    Robe(){
        type = ArmorType::MAGIC;
        absorbation = 1;
    }

};

class VladimirOffering: public Armor{

public:
    VladimirOffering(){
        type = ArmorType::HEAVY;
        absorbation = 10;
    }

};
#endif //BATTLEFORHONOUR_ARMOR_H
