#ifndef ARCHER_H
#define ARCHER_H
#include "LongRange.h"

class Archer : public LongRange {
public:
    explicit Archer(std::pair<int, int>, std::string = "");
    std::string type() const final;
};


#endif //ARCHER_H
