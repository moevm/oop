//
// Created by kot on 10.05.2020.
//

#ifndef ARMOR_H
#define ARMOR_H
#include "neutralObj.h"

class Armor
{
public:
    virtual void use(Unit&) = 0;
    virtual ~Armor() = default;
};

class GetArmor : public NeutralObj
{
private:
    Armor* armor;
public:
    GetArmor(Armor* armor) : armor(armor) {}

    ~GetArmor()
    {
        delete armor;
    }

    void operator += (Unit& unit)
    {
        armor->use(unit);
    }

    std::string characteristics() const {return "armor";}

    std::string getType() const {return "neutral";}
};

class MithrilHauberk : public Armor
{
public:
    void use(Unit& unit)
    {
        unit.getCharacteristics()->setArmor(unit.getCharacteristics()->getArmor() + 30);
    }
};

class MantleOfInvisibility : public Armor
{
public:
    void use(Unit& unit)
    {
        unit.getCharacteristics()->setArmor(unit.getCharacteristics()->getArmor() + 50);
    }
};

class Helmet : public Armor
{
public:
    void use(Unit& unit)
    {
        unit.getCharacteristics()->setArmor(unit.getCharacteristics()->getArmor() + 20);
    }
};


#endif //ARMOR_H
