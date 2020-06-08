#pragma once
#include <iostream>
#include "unit_base.h"



class Range_unit : public Unit {

};

class Archer : public Range_unit {
public:
	Archer();
};

class Mage : public Range_unit {
public:
	Mage();
};