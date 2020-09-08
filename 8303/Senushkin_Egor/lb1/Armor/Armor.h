//
// Created by egor on 15.03.2020.
//

#ifndef OOP_LB1__2_ARMOR_H
#define OOP_LB1__2_ARMOR_H


enum class ArmorType{

    HEAVY,
    MEDIUM,
    LIGHT

};

class Armor {
protected:
    int BlockingDamage;
    ArmorType type;
public:
    Armor() = default;
    virtual ~Armor() = default;



};

#endif //OOP_LB1__2_ARMOR_H
