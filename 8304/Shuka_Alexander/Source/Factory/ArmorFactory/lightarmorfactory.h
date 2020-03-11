#ifndef LIGHTARMORFABRIC_H
#define LIGHTARMORFABRIC_H

#include "armorfactory.h"

#include "Atributes/Armor/lightarmor.h"


class LightArmorFactory : public ArmorFactory
{
public:
    explicit LightArmorFactory() = default;
    virtual ~LightArmorFactory() = default;

    virtual std::unique_ptr<Armor> createArmor() override;
};

#endif // LIGHTARMORFABRIC_H
