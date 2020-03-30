#ifndef UNITS_H
#define UNITS_H

#include "qstring.h"
#include "observer.h"

class Unit:public Subject
{
    bool choose;
    char baseType;

public:
    int x;
    int y;
    char designation;
    bool movement;
    bool attacks;
    QString className;

    class Params
    {
        public:
            int health;
            int armor;
            int distance;
            int damage;
        } param;
    void move(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    void enableAttack(bool t);
    void enableMovement(bool t);
    void buffHealth(float n);
    void buffAttack(float n);
    void buffArmor(float n);
    void setChoose(bool t);
    void setArmy(char c);
    void attackThis(int n);
    QString getClassName();
    int getHealth();
    int getDamage();
    int getX();
    int getY();
    bool getChoose();
    bool canMove();
    char getArmy();
};


class Stormtrooper : public Unit
{

};

class HumanStormtrooper : public Stormtrooper
{
public:
    HumanStormtrooper(int x, int y)
    {
        this->param.health = 100;
        this->param.armor = 10;
        this->param.damage = 20;
        this->x = x;
        this->y = y;
        this->designation = 'S';
        this->className = "Trooper";
        this->setChoose(true);
        this->setArmy('H');
    }
};

class AlienStormtrooper : public Stormtrooper
{
public:
    AlienStormtrooper(int x, int y)
    {
        this->param.health = 80;
        this->param.armor = 12;
        this->param.damage = 24;
        this->x = x;
        this->y = y;
        this->designation = 'S';
        this->className = "Trooper";
        this->setChoose(true);
        this->setArmy('A');
    }
};

class Droid : public Unit
{

};

class HumanDroid : public Droid
{
public:
    HumanDroid(int x, int y)
    {
        this->param.health = 50;
        this->param.armor = 5;
        this->param.damage = 35;
        this->x = x;
        this->y = y;
        this->designation = 'D';
        this->className = "Droid";
        this->setChoose(true);
        this->setArmy('H');
    }
};

class AlienDroid : public Droid
{
public:
    AlienDroid(int x, int y)
    {
        this->param.health = 62;
        this->param.armor = 7;
        this->param.damage = 29;
        this->x = x;
        this->y = y;
        this->designation = 'D';
        this->className = "Droid";
        this->setChoose(true);
        this->setArmy('A');
    }
};

class PlasmaTank : public Unit
{

};

class HumanPlasmaTank : public PlasmaTank
{
public:
    HumanPlasmaTank(int x, int y)
    {
        this->param.health = 90;
        this->param.armor = 3;
        this->param.damage = 35;
        this->x = x;
        this->y = y;
        this->designation = 'P';
        this->className = "Tank";
        this->setChoose(true);
        this->setArmy('H');
    }
};

class AlienPlasmaTank : public PlasmaTank
{
public:
    AlienPlasmaTank(int x, int y)
    {
        this->param.health = 90;
        this->param.armor = 3;
        this->param.damage = 35;
        this->x = x;
        this->y = y;
        this->designation = 'P';
        this->className = "Tank";
        this->setChoose(true);
        this->setArmy('A');
    }
};

class AbstractFactory
{
    virtual Stormtrooper* createStormtrooper(int x, int y) = 0;
    virtual Droid* createDroid(int x, int y) = 0;
    virtual PlasmaTank* createPlasmaTank(int x, int y) = 0;
    //virtual ~AbstractFactory() {};
};

class HumanArmyFactory : public AbstractFactory
{
public:
    Stormtrooper* createStormtrooper(int x, int y)
    {
        return new HumanStormtrooper(x, y);
    }
    Droid* createDroid(int x, int y)
    {
        return new HumanDroid(x, y);
    }
    PlasmaTank* createPlasmaTank(int x, int y)
    {
        return new HumanPlasmaTank(x, y);
    }

};

class AlienArmyFactory : public AbstractFactory
{
public:
    Stormtrooper* createStormtrooper(int x, int y)
    {
        return new AlienStormtrooper(x, y);
    }
    Droid* createDroid(int x, int y)
    {
        return new AlienDroid(x, y);
    }
    PlasmaTank* createPlasmaTank(int x, int y)
    {
        return new AlienPlasmaTank(x, y);
    }
};

#endif // UNITS_H
