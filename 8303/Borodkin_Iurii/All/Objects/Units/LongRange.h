#ifndef LONGRANGE_H
#define LONGRANGE_H
#include "Unit.h"

class LongRange : public Unit
{
protected:
    LongRange(string = "");

    explicit LongRange(const LongRange&) = default;

    string type() const override;
};


#endif //LONGRANGE_H
