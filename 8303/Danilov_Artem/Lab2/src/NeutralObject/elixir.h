//
// Created by kot on 10.05.2020.
//

#ifndef ELIXIR_H
#define ELIXIR_H
#include "neutralObj.h"

class Elixir
{
public:
    virtual ~Elixir() = default;
    virtual void use(Unit&) = 0;
};

class GetElixir : public NeutralObj
{
private:
    Elixir* elixir;
public:
    GetElixir(Elixir* elixir) : elixir(elixir) {}

    ~GetElixir()
    {
        delete elixir;
    }

    void operator += (Unit& unit)
    {
        elixir->use(unit);
    }

    std::string characteristics() const {return "elixir";}

    std::string getType() const {return "neutral";}
};

class Swallow : public Elixir
{
public:
    void use(Unit& unit)
    {
        unit.getCharacteristics()->setHealth(unit.getCharacteristics()->getHealth() + 1000);
    }
};

class Thunderbolt : public Elixir
{
public:
    void use (Unit& unit)
    {
        unit.getCharacteristics()->setHealth(unit.getCharacteristics()->getHealth() + 700);
        unit.getCharacteristics()->setDamage(unit.getCharacteristics()->getDamage() + 70);
    }
};

class TheAncientDrink : public Elixir
{
public:
    void use (Unit& unit)
    {
        auto tmp = std::rand()%50 + 1;
        //auto flag = (std::rand() % 2 == 1) ? 1 : -1;
        unit.getCharacteristics()->setHealth(unit.getCharacteristics()->getHealth() + tmp  * 10);
        unit.getCharacteristics()->setDamage(unit.getCharacteristics()->getDamage() + tmp );
        unit.getCharacteristics()->setArmor(unit.getCharacteristics()->getArmor() + tmp );
    }
};


#endif //ELIXIR_H
