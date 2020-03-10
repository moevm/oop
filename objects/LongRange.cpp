#include "LongRange.h"
#include <utility>

LongRange::LongRange(std::string name) : Unit(std::move(name))
{}

std::string LongRange::type() const {return "LongRange";}
