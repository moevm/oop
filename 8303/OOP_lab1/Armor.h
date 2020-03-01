
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

};

#endif //OOP_LAB1_ARMOR_H
