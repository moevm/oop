#ifndef RIDER_H
#define RIDER_H
#include "Unit.h"

class Rider : public Unit
{
protected:
    explicit Rider(string = "");

    string type() const override;
};


#endif //RIDER_H
