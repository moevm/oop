#ifndef NEUTRALOBJ_H
#define NEUTRALOBJ_H

#include "landscape.h"
#include "units.h"


class Neutral
{  
public:
    class Interaction
    {
    public:
        virtual ~Interaction(){}
        virtual void interact(Unit * unit) = 0;
    };

    class Interactor
    {
        Interaction * i;
    public:
        Interactor(Interaction * Interaction) : i(Interaction) {}
        ~Interactor(){delete i;}
        void interact(Unit * unit)
        {
            i->interact(unit);
        }
    };

    Interactor* i;
    virtual void operator>>(Unit * unit) = 0;
    Neutral(){}
    char name;
    char getName();
};



class FieldMine: public Neutral
{
    class TrooperIt: public Interaction
    {
        void interact(Unit * unit);
    };
    class DroidIt: public Interaction
    {
        void interact(Unit * unit);
    };
    class TankIt: public Interaction
    {
        void interact(Unit * unit);
    };
public:
    void operator>>(Unit* unit);
    FieldMine()
    {
        this->name = 'M';
    }
};

class Village: public Neutral
{
    class TrooperIt: public Interaction
    {
        void interact(Unit * unit);
    };
    class DroidIt: public Interaction
    {
        void interact(Unit * unit);
    };
    class TankIt: public Interaction
    {
        void interact(Unit * unit);
    };
public:
    void operator>>(Unit* unit);
    Village()
    {
        this->name = 'V';
    }
};

class Workshop: public Neutral
{
    class TrooperIt: public Interaction
    {
        void interact(Unit * unit);
    };
    class DroidIt: public Interaction
    {
        void interact(Unit * unit);
    };
    class TankIt: public Interaction
    {
        void interact(Unit * unit);
    };
public:
    void operator>>(Unit* unit);
    Workshop()
    {
        this->name = 'W';
    }
};

class Altar: public Neutral
{
    class TrooperIt: public Interaction
    {
        void interact(Unit * unit);
    };
    class DroidIt: public Interaction
    {
        void interact(Unit * unit);
    };
    class TankIt: public Interaction
    {
        void interact(Unit * unit);
    };
public:
    void operator>>(Unit* unit);
    Altar()
    {
        this->name = 'A';
    }
};

class NoneObject : public Neutral
{
    class TrooperIt: public Interaction
    {
        void interact(Unit * unit);
    };
    class DroidIt: public Interaction
    {
        void interact(Unit * unit);
    };
    class TankIt: public Interaction
    {
        void interact(Unit * unit);
    };
public:
    void operator>>(Unit * unit);
    NoneObject()
    {
        this->name = 'O';
    }

};
#endif // NEUTRALOBJ_H
