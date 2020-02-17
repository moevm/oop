#ifndef LONGRANGE_H
#define LONGRANGE_H
#include "Unit.h"

class LongRange : public Unit {
public:
    enum Ranges {
        R_ARCHER = 3,
        R_WIZARD = 2
    };
protected:
    unsigned _range;
    LongRange(std::pair<int, int>, std::string);
    std::string type() const override;
    unsigned range() const;
};


#endif //LONGRANGE_H
