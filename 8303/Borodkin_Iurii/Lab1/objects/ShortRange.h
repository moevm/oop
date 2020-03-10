#ifndef SHORTRANGE_H
#define SHORTRANGE_H
#include "Unit.h"

class ShortRange : public Unit {
protected:
    explicit ShortRange(std::string = "");
    explicit ShortRange(const ShortRange&) = default;
    std::string type() const override;
};


#endif //SHORTRANGE_H
