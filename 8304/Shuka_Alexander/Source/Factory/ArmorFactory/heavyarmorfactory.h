#ifndef HEAVYARMORFABRIC_H
#define HEAVYARMORFABRIC_H

#include "armorfactory.h"

#include "Atributes/Armor/heavyarmor.h"


class HeavyArmorFactory : public ArmorFactory
{
public:
    virtual std::shared_ptr<Armor> createArmor() const override;
};

#endif // HEAVYARMORFABRIC_H
