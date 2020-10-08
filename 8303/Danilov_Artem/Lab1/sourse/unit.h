//
// Created by kot on 25.02.2020.
//

#ifndef UNIT_H
#define UNIT_H

#include "field.h"
#include "characteristics.h"


class Unit : public FieldItem
{
public:
    Unit() {}
    Unit(Unit &unit);
    virtual ~Unit() = default;

    virtual bool isMovable() {
       return movable;
    }
    virtual std::string shortName() = 0;
    virtual std::string about();
    virtual FieldItem *itemCopy() = 0;

    virtual void move(int x, int y);

protected:
    std::string name;
    bool movable = true;
    Characteristics naturalStats;
};

class Radiant : public Unit{
public:
    virtual FieldItem *itemCopy() = 0;
};

class Knight : public Radiant{
public:
    Knight();
    std::string shortName() {return "Knight";}
    FieldItem *itemCopy(){
        return new Knight(*this);
    }
};

class Dryad : public Radiant{
public:
    // todo heal if health < 10 % every 3th turn  on 30% of hp
    Dryad();
    std::string shortName() {return "Dryad";}
    FieldItem *itemCopy(){
        return new Dryad(*this);
    }
};

class Dragon : public Radiant{
public:
    Dragon();
    std::string shortName() {return "Dragon";}
    FieldItem *itemCopy(){
        return new Dragon(*this);
    }
};

class Dire : public Unit {
public:
    virtual FieldItem *itemCopy() = 0;
};

class Ork : public Dire {
public:
    Ork();
    std::string shortName() {return "Ork";}
    FieldItem *itemCopy(){
        return new Ork(*this);
    }
};

class Witch : public Dire {
    // support 2 death and  all_char/3 orks
public:
    Witch();
    std::string shortName() {return "Witch";}
    FieldItem *itemCopy(){
        return new Witch(*this);
    }
};

class Chimera : public Dire {
public:
    Chimera();
    std::string shortName() {return "Chimera";}
    FieldItem *itemCopy(){
        return new Chimera(*this);
    }
};

class UnitFactory {
public:
    virtual Radiant *createRadiant() = 0;
    virtual Dire *createDire() = 0;
};

class MeleeFactory : public UnitFactory {
public:
    Radiant * createRadiant(){
        return new Knight();
    }
    Dire * createDire(){
        return new Ork();
    }
};

class SupportFactory : public UnitFactory {
public:
    Radiant * createRadiant(){
        return new Dryad();
    }
    Dire * createDire(){
        return new Witch();
    }
};

class RangeFactory : public UnitFactory {
public:
    Radiant * createRadiant(){
        return new Dragon();
    }
    Dire * createDire(){
        return new Chimera();
    }
};


#endif //UNIT_H
