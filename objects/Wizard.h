#ifndef WIZARD_H
#define WIZARD_H
#include "LongRange.h"

class Wizard : public LongRange {
public:
    explicit Wizard(std::string = "");
    explicit Wizard(const Wizard&);
    Wizard(Wizard&&);
    std::string type() const final;
};


#endif //WIZARD_H
