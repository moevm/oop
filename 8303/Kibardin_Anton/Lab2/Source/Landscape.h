//
// Created by anton on 11.03.2020.
//

#ifndef OOP_1_LANDSCAPE_H
#define OOP_1_LANDSCAPE_H


#include "Units/Unit.h"

class Landscape {
public:

    virtual void impact(Unit*) = 0;

    virtual char getType() const= 0;

    virtual bool isAvailable(const Unit* ) const = 0;


};

class Mountains: public Landscape
{
public:

    void impact(Unit*) override;// can

    char getType() const override;

    bool isAvailable(const Unit* ) const override;

};

class Grass: public Landscape
{
public:

    void impact(Unit*) override;

    char getType() const override;

    bool isAvailable(const Unit* ) const override;
};

class Forest: public Landscape
{
public:

    void impact(Unit* tmp) override;

    char getType() const override;

    bool isAvailable(const Unit* ) const override;
};
#endif //OOP_1_LANDSCAPE_H
