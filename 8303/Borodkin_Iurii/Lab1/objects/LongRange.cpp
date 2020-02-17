#include "LongRange.h"
#include <utility>

LongRange::LongRange(std::pair<int, int> coordinates, std::string name) :
                    Unit(coordinates, std::move(name)), _range(0)
{}

std::string LongRange::type() const {return "LongRange";}

unsigned LongRange::range() const {return _range;}
