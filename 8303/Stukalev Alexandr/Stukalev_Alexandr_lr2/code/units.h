#ifndef UNITS_H
#define UNITS_H

#include "qstring.h"
#include "observer.h"

class Unit:public Subject
{
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
    bool canMove();
    void buffHealth(float n);
    void buffAttack(float n);
    void buffArmor(float n);
    QString getClassName();
    int getHealth();
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
