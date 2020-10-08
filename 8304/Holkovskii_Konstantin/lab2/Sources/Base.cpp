#include "../Headers/Base.h"

void Base::addUnit(const Point &a) {
    Units.components.insert(a);
    ++count;
}

void Base::removeUnit(Point const &a) {
    Units.components.erase(a);
    --count;
}

Base::Base(int a):Hp(1000), max_count(a), count(0) {}

void Node::SayHi() {}

void Composite::SayHi() {}
