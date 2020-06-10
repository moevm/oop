#ifndef WIZARD_H
#define WIZARD_H
#include "LongRange.h"

class Wizard : public LongRange
{
public:
    explicit Wizard(unsigned = 0, string = "");

    explicit Wizard(Attributes*, unsigned = 0);

    Wizard(const Wizard&);

    Wizard(Wizard&&);

    unsigned travelDistance() const override;

    void getDamage(unsigned) override;

    void heal(unsigned) override;

    string type() const final;
};


#endif //WIZARD_H
