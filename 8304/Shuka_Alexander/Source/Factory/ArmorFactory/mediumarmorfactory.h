#ifndef MEDIUMARMORFABRIC_H
#define MEDIUMARMORFABRIC_H

#include "armorfactory.h"

#include "Atributes/Armor/mediumarmor.h"


class MediumArmorFactory : public ArmorFactory
{
public:
    explicit MediumArmorFactory() = default;
    virtual ~MediumArmorFactory() = default;

    virtual std::unique_ptr<Armor> createArmor() override;
};

#endif // MEDIUMARMORFABRIC_H
