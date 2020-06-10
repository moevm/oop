#ifndef CENTAUR_H
#define CENTAUR_H
#include "Rider.h"

class Centaur : public Rider
{
public:
    explicit Centaur(unsigned = 0, string = "");

    explicit Centaur(Attributes*, unsigned = 0);

    Centaur(const Centaur&);

    Centaur(Centaur&&);

    unsigned travelDistance() const override;

    void getDamage(unsigned) override;

    void heal(unsigned) override;

    string type() const final;
};


#endif //CENTAUR_H
