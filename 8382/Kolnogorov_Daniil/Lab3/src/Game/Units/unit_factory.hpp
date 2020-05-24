#pragma once

class UnitInterface;

class UnitFactory {
public:
    virtual ~UnitFactory() = default;
    virtual UnitInterface* create() = 0;
};
