#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <utility>
#include "Attributes.h"
#include "Neuturals/Pack.h"
#include "Mediator/Mediator.h"

class Unit;

using std::string;

enum class Moves : int
{
    LEFT,
    UP,
    RIGHT,
    DOWN
};

class Object
{
protected:

    Attributes* attr;

    string _name;

    explicit Object(string = "");

public:

    Mediator* mediator;

    int health() const;

    unsigned range() const;

    unsigned damage() const;

    unsigned armor() const;

    unsigned mana() const;

    string &name();

    unsigned player = 0;

    virtual bool empty() const;

    virtual bool createUnit(Unit*);

    virtual Unit* getUnit();

    virtual string type() const = 0;

    virtual unsigned travelDistance() const = 0;

    virtual void attack() = 0;

    virtual void heal(unsigned) = 0;

    virtual void getDamage(unsigned) = 0;

    friend Object& operator+=(Object&, Pack&);

    virtual ~Object();
};

#endif // OBJECT_H
