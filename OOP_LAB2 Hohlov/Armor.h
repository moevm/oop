
#ifndef OOP_LAB1_ARMOR_H
#define OOP_LAB1_ARMOR_H

enum class ArmorType{

    HEAVY,
    MEDIUM,
    LIGHT

};

class Armor {

protected:

    ArmorType type;
    int damageResistance;

public:

    Armor(){}
    int getdamageResistance() const { return damageResistance; }
    ArmorType getType(){ return type; }

    bool operator==(Armor &other){

        return type == other.type && damageResistance == other.damageResistance;

    }

    Armor& operator=(const Armor& other){

        if (this == &other) return *this;
        type = other.type;
        damageResistance = other.damageResistance;
        return *this;

    }

};



#endif //OOP_LAB1_ARMOR_H
