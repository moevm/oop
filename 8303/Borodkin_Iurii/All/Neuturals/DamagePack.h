#ifndef DAMAGEPACK_H
#define DAMAGEPACK_H
#include "Pack.h"
#include "Objects/Units/Unit.h"

class DamagePack : public Pack
{
public:
    DamagePack();
    Attributes buff() override;
    std::string type() override;
};

class DamageStrategy
{
public:
    void buff(Object*, Pack**);
};

#endif // DAMAGEPACK_H
