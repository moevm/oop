#ifndef HEALTHPACK_H
#define HEALTHPACK_H
#include "Pack.h"
#include "Objects/Units/Unit.h"

class HealthPack : public Pack
{
public:
    HealthPack();
    Attributes buff() override;
    std::string type() override;
};

class HealthStrategy
{
public:
    void buff(Object*, Pack**);
};

#endif // HEALTHPACK_H
