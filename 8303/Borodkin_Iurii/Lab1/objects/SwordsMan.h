#ifndef SWORDSMAN_H
#define SWORDSMAN_H
#include "ShortRange.h"

class SwordsMan : public ShortRange {
public:
    explicit SwordsMan(std::pair<int, int>, std::string = "");
    std::string type() const final;
};


#endif //SWORDSMAN_H
