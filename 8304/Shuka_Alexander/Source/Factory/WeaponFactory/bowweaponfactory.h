#ifndef BOWWEAPONFactory_H
#define BOWWEAPONFABRIC_H

#include "weaponfactory.h"

#include "Atributes/Weapon/bow.h"


class BowWeaponFactory : public WeaponFactory
{
public:
    explicit BowWeaponFactory() = default;
    virtual ~BowWeaponFactory() = default;

    virtual std::unique_ptr<Weapon> createWeapon() override;
};

#endif // BOWWEAPONFactory_H
