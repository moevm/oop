#ifndef LIGHTARMORFABRIC_H
#define LIGHTARMORFABRIC_H

#include "armorfactory.h"

#include "Atributes/Armor/lightarmor.h"


class LightArmorFactory : public ArmorFactory
{
public:
    virtual std::shared_ptr<Armor> createArmor() const override;
};

#endif // LIGHTARMORFABRIC_H
