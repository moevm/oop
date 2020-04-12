//
// Created by anton on 11.03.2020.
//

#ifndef OOP_1_NEUTRAL_H
#define OOP_1_NEUTRAL_H


#include "Units/Unit.h"

class Unit;

class Neutral {
public:

    virtual void getEffect(Unit*) = 0;

    virtual char getType() const = 0;

    void operator+=(Unit*);
};

class ForcePortion: public Neutral
{
public:

    void getEffect(Unit*) override ;

    char getType() const override;
};

class Stew: public Neutral
{
public:

    void getEffect(Unit*) override;

    char getType() const override;
};

class Poison: public Neutral
{
public:

    void getEffect(Unit*) override;

    char getType() const override;
};

class RangePortion: public Neutral
{
public:

    void getEffect(Unit*) override;

    char getType() const override;
};

#endif //OOP_1_NEUTRAL_H
