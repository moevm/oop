#pragma once

#include "Unit.h"


class UnitFactory {
public:
    Unit* produce(uint8_t unitType, Point point, Base* base);
};
