#ifndef MEDIUMARMORFABRIC_H
#define MEDIUMARMORFABRIC_H

#include "armorfactory.h"

#include "Atributes/Armor/mediumarmor.h"


class MediumArmorFactory : public ArmorFactory
{
public:
    virtual std::shared_ptr<Armor> createArmor() const override;
};

#endif // MEDIUMARMORFABRIC_H
