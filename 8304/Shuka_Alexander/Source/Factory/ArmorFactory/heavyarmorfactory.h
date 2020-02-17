#ifndef HEAVYARMORFABRIC_H
#define HEAVYARMORFABRIC_H

#include "armorfactory.h"

#include "Atributes/Armor/heavyarmor.h"


class HeavyArmorFactory : public ArmorFactory
{
public:
    explicit HeavyArmorFactory() = default;
    virtual ~HeavyArmorFactory() = default;

    virtual std::unique_ptr<Armor> createArmor() override;
};

#endif // HEAVYARMORFABRIC_H
