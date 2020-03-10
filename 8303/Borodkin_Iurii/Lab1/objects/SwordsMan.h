#ifndef SWORDSMAN_H
#define SWORDSMAN_H
#include "ShortRange.h"

class SwordsMan : public ShortRange {
public:
    explicit SwordsMan(std::string = "");
    explicit SwordsMan(const SwordsMan&);
    SwordsMan(SwordsMan&&);
    std::string type() const final;
};


#endif //SWORDSMAN_H
