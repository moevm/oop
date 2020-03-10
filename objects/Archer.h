#ifndef ARCHER_H
#define ARCHER_H
#include "LongRange.h"

class Archer : public LongRange {
public:
    explicit Archer(std::string = "");
    explicit Archer(const Archer&);
    Archer(Archer&&);
    std::string type() const final;
};


#endif //ARCHER_H
