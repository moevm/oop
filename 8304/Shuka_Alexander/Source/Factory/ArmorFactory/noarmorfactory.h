#ifndef NOARMORFABRIC_H
#define NOARMORFABRIC_H

#include "armorfactory.h"

#include "Atributes/Armor/noarmor.h"


class NoArmorFactory : public ArmorFactory
{
public:
    explicit NoArmorFactory() = default;
    virtual ~NoArmorFactory() = default;

    virtual std::unique_ptr<Armor> createArmor() override;
};

#endif // NOARMORFABRIC_H
