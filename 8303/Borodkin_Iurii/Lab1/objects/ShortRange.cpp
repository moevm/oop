#include "ShortRange.h"
#include <utility>

ShortRange::ShortRange(std::pair<int, int> coordinates, std::string name) :
            Unit(coordinates, std::move(name)), _armor(0)
{}

unsigned ShortRange::armor() const {return _armor;}

std::string ShortRange::type() const {return "ShortRange";}
