#ifndef UNIST_TYPES_H
#define UNIST_TYPES_H
#include "units.h"

class Stormtrooper : public Unit
{

};

class HumanStormtrooper : public Stormtrooper
{
public:
    HumanStormtrooper(int x, int y)
    {
        health = 100;
        armor = 10;
        damage = 20;
        this->x = x;
        this->y = y;
        this->designation = 'S';
    }
};

class AlienStormtrooper : public Stormtrooper
{
public:
    AlienStormtrooper(int x, int y)
    {
        health = 80;
        armor = 12;
        damage = 24;
        this->x = x;
        this->y = y;
        this->designation = 'S';
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
        health = 50;
        armor = 5;
        damage = 35;
        this->x = x;
        this->y = y;
        this->designation = 'D';
    }
};

class AlienDroid : public Droid
{
public:
    AlienDroid(int x, int y)
    {
        health = 62;
        armor = 7;
        damage = 29;
        this->x = x;
        this->y = y;
        this->designation = 'D';
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
        health = 90;
        armor = 3;
        damage = 35;
        this->x = x;
        this->y = y;
        this->designation = 'P';
    }
};

class AlienPlasmaTank : public PlasmaTank
{
public:
    AlienPlasmaTank(int x, int y)
    {
        health = 90;
        armor = 3;
        damage = 35;
        this->x = x;
        this->y = y;
        this->designation = 'P';
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
#endif // UNIST_TYPES_H
