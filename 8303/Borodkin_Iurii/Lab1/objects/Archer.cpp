#include "Archer.h"
#include <utility>

Archer::Archer(std::pair<int, int> coords, std::string name) :
                LongRange(coords, std::move(name)) {
    _range  = R_ARCHER  ;
    _health = H_ARCHER  ;
    _attack = ATT_ARCHER;
}

std::string Archer::type() const {return "Archer";}
