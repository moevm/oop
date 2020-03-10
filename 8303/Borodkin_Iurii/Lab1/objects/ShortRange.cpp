#include "ShortRange.h"
#include <utility>

ShortRange::ShortRange(std::string name) : Unit(std::move(name))
{}

std::string ShortRange::type() const {return "ShortRange";}
