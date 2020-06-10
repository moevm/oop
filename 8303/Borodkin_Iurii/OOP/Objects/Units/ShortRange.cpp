#include "ShortRange.h"
#include <utility>

ShortRange::ShortRange(string name) : Unit(std::move(name))
{}

string ShortRange::type() const {return "ShortRange";}
