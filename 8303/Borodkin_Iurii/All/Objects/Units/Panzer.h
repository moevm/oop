#ifndef PANZER_H
#define PANZER_H
#include "Rider.h"

class Panzer : public Rider
{
public:
    explicit Panzer(unsigned = 0, string = "");

    explicit Panzer(Attributes*, unsigned = 0);

    Panzer(const Panzer&);

    Panzer(Panzer&&);

    unsigned travelDistance() const override;

    void getDamage(unsigned) override;

    void heal(unsigned) override;

    string type() const final;
};


#endif //PANZER_H
