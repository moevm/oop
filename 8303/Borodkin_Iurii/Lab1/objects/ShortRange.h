#ifndef SHORTRANGE_H
#define SHORTRANGE_H
#include "Unit.h"

class ShortRange : public Unit {
public:
    enum Armors {
        ARM_SWORD    = 250,
        ARM_SPEARMAN = 100
    };
protected:
    unsigned _armor;
    explicit ShortRange(std::pair<int, int>, std::string = "");
    std::string type() const override;
    unsigned armor() const;
};


#endif //SHORTRANGE_H
