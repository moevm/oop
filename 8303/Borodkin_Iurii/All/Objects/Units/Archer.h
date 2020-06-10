#ifndef ARCHER_H
#define ARCHER_H
#include "LongRange.h"

class Archer : public LongRange
{
public:
    explicit Archer(unsigned = 0, string = "");

    explicit Archer(Attributes*, unsigned = 0);

    Archer(const Archer&);

    Archer(Archer&&);

    unsigned travelDistance() const override;

    void getDamage(unsigned) override;

    void heal(unsigned) override;

    string type() const final;
};


#endif //ARCHER_H
