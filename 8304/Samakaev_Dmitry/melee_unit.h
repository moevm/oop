#pragma once
#include <iostream>
#include "unit_base.h"


class Melee_unit: public Unit {

};

class Knight : public Melee_unit {
public:
	Knight();
};

class Rogue : public Melee_unit {
public:
	Rogue();
};