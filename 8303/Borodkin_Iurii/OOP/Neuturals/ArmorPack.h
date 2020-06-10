#ifndef ARMORPACK_H
#define ARMORPACK_H
#include "Pack.h"
#include "Objects/Units/Unit.h"

class ArmorPack : public Pack
{
public:
    ArmorPack();
    Attributes buff() override;
    std::string type() override;
};

class ArmorStrategy
{
public:
    void buff(Object*, Pack**);
};

#endif // ARMORPACK_H
