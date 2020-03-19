#ifndef ARMORFABRIC_H
#define ARMORFABRIC_H

#include <memory>

#include "Atributes/Armor/armor.h"


class ArmorFactory
{
public:
    virtual ~ArmorFactory() = default;

    virtual std::shared_ptr<Armor> createArmor() const = 0;
};

#endif // ARMORFABRIC_H
