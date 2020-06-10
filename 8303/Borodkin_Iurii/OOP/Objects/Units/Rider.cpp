#include "Rider.h"
#include <utility>

Rider::Rider(string name) : Unit(std::move(name))
{}

string Rider::type() const {return "Rider";}
