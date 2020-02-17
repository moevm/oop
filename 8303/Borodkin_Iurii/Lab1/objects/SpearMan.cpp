#include "SpearMan.h"
#include <utility>

SpearMan::SpearMan(std::pair<int, int> coords, std::string name) :
        ShortRange(coords, std::move(name)) {
    _armor  = ARM_SPEARMAN;
    _health = H_SPEARMAN  ;
    _attack = ATT_SPEARMAN;
}

std::string SpearMan::type() const {return "SpearMan";}
