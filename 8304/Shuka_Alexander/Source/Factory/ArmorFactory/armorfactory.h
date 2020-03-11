#ifndef ARMORFABRIC_H
#define ARMORFABRIC_H

#include <memory>

#include "Atributes/Armor/armor.h"


class ArmorFactory
{
public:
    explicit ArmorFactory() = default;
    virtual ~ArmorFactory() = default;

    virtual std::unique_ptr<Armor> createArmor() = 0;
};

#endif // ARMORFABRIC_H
