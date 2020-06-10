#ifndef SWORDSMAN_H
#define SWORDSMAN_H
#include "ShortRange.h"

class SwordsMan : public ShortRange
{
public:
    explicit SwordsMan(unsigned = 0, string = "");

    explicit SwordsMan(Attributes*, unsigned = 0);

    SwordsMan(const SwordsMan&);

    SwordsMan(SwordsMan&&);

    unsigned travelDistance() const override;

    void getDamage(unsigned) override;

    void heal(unsigned) override;

    string type() const final;
};


#endif //SWORDSMAN_H
