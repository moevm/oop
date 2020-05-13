//
// Created by kot on 10.05.2020.
//

#ifndef CURSE_H
#define CURSE_H
#include "neutralObj.h"

class Curse
{
public:
    virtual ~Curse() = default;
    virtual void use(Unit&) = 0;
};

class GetCurse : public NeutralObj
{
private:
    Curse* curse;
public:
    GetCurse(Curse* curse) : curse(curse) {}

    ~GetCurse()
    {
        delete curse;
    }

    void operator += (Unit& unit)
    {
        curse->use(unit);
    }

    std::string characteristics() const {return "curse";}

    std::string getType() const {return "neutral";}
};

class AncientMold : public Curse
{
public:
    void use(Unit& unit)
    {
        unit.getCharacteristics()->setArmor(unit.getCharacteristics()->getArmor()/10*6);
    }
};

class ChineseGlasses : public Curse
{
public:
    void use (Unit& unit)
    {
        unit.getCharacteristics()->setDamage(unit.getCharacteristics()->getDamage()/10*6);
    }
};

class Covid : public Curse
{
public:
    void use (Unit& unit)
    {
        unit.getCharacteristics()->setHealth(unit.getCharacteristics()->getHealth()/2);
    }
};



#endif //CURSE_H
