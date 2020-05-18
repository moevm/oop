#pragma once

#include "unit_factory.hpp"

template <typename T>
class ConcreteUnitFactory : public UnitFactory {
public:
    UnitInterface* create() override { return new T(); };
};
