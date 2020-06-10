#ifndef SPEARMAN_H
#define SPEARMAN_H
#include "ShortRange.h"

class SpearMan : public ShortRange
{
public:
    explicit SpearMan(unsigned = 0, string = "");

    explicit SpearMan(Attributes*, unsigned = 0);

    explicit SpearMan(const SpearMan&);

    SpearMan(SpearMan&&);

    unsigned travelDistance() const override;

    void getDamage(unsigned) override;

    void heal(unsigned) override;

    string type() const final;
};


#endif //SPEARMAN_H
