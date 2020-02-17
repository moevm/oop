#include "SwordsMan.h"
#include <utility>

SwordsMan::SwordsMan(std::pair<int, int> coords, std::string name) :
                    ShortRange(coords, std::move(name))
{
    _health = H_SWORDSMAN  ;
    _armor  = ARM_SWORD    ;
    _attack = ATT_SWORDSMAN;
}

std::string SwordsMan::type() const {return "SwordsMan";}
