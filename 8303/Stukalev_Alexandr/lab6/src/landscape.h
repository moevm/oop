#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include "units.h"

class Landscape
{
        friend class RiverProxy;
        friend class ForestProxy;
        friend class MountainProxy;
        friend class PlainProxy;
        Landscape(){}

        char name;

        void disableMove(Unit * unit);
        void enableMove(Unit * unit);
        void disableAttack(Unit * unit);
        void enableAttack(Unit * unit);
        void swirl(Unit * unit);
        void buffHeal(Unit* unit, float n);
        void buffAttack(Unit* unit, float n);
public:
        char getName();

        virtual void interact(Unit * unit) = 0;
        virtual bool isInteract(Unit * unit) = 0;
};

class RiverProxy : public Landscape
{
    Landscape * land;
public:
    RiverProxy()
    {
        this->name = 'R';
    }
    void interact(Unit * unit);
    bool isInteract(Unit * unit);
};

class ForestProxy : public Landscape
{
    Landscape * land;
public:
    ForestProxy()
    {
        this->name = 'F';
    }
    void interact(Unit * unit);
    bool isInteract(Unit * unit);
};
class MountainProxy : public Landscape
{
    Landscape * land;
public:
    MountainProxy()
    {
        this->name = 'M';
    }
    void interact(Unit * unit);
    bool isInteract(Unit * unit);
};

class PlainProxy : public Landscape
{
    Landscape* land;
public:
    PlainProxy()
    {
        this->name = 'P';
    }
    void interact(Unit * unit);
    bool isInteract(Unit * unit);

};

#endif // LANDSCAPE_H
