#ifndef LONGRANGE_H
#define LONGRANGE_H
#include "Unit.h"

class LongRange : public Unit {
protected:
    LongRange(std::string = "");
    explicit LongRange(const LongRange&) = default;
    std::string type() const override;
};


#endif //LONGRANGE_H
