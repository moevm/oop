#include "Wizard.h"
#include <utility>

Wizard::Wizard(std::pair<int, int> coords, std::string name) :
        LongRange(coords, std::move(name)) {
    _range  = R_WIZARD  ;
    _health = H_WIZARD  ;
    _attack = ATT_WIZARD;
}

std::string Wizard::type() const {return "Wizard";}
