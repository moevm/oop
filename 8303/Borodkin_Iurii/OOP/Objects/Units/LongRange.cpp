#include "LongRange.h"
#include <utility>

LongRange::LongRange(string name) : Unit(std::move(name))
{}

string LongRange::type() const {return "LongRange";}
