#ifndef SHORTRANGE_H
#define SHORTRANGE_H
#include "Unit.h"

class ShortRange : public Unit
{
protected:
    explicit ShortRange(string = "");

    explicit ShortRange(const ShortRange&) = default;

    string type() const override;
};


#endif //SHORTRANGE_H
