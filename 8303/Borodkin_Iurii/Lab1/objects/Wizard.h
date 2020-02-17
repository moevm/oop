#ifndef WIZARD_H
#define WIZARD_H
#include "LongRange.h"

class Wizard : public LongRange {
public:
    explicit Wizard(std::pair<int, int>, std::string = "");
    std::string type() const final;
};


#endif //WIZARD_H
