#include "Panzer.h"
#include <utility>

Panzer::Panzer(std::pair<int, int> coordinates, std::string name) :
                Rider(coordinates, std::move(name))
{
    _health = H_PANZER  ;
    _attack = ATT_PANZER;
}

std::string Panzer::type() const {return "Panzer";}
