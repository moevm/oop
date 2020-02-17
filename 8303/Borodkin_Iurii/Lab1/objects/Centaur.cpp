#include "Centaur.h"
#include <utility>

Centaur::Centaur(std::pair<int, int> coordinates, std::string name) :
                Rider(coordinates, std::move(name))
{
    _health = H_CENTAUR  ;
    _attack = ATT_CENTAUR;
}

std::string Centaur::type() const {return "Centaur";}
