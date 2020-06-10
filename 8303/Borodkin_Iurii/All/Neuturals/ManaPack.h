#ifndef MANAPACK_H
#define MANAPACK_H
#include "Pack.h"
#include "Objects/Units/Unit.h"

class ManaPack : public Pack
{
public:
    ManaPack();
    Attributes buff() override;
    std::string type() override;
};

class ManaStrategy
{
public:
    void buff(Object*, Pack**);
};


#endif // MANAPACK_H
