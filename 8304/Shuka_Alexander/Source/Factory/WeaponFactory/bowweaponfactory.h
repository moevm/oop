#ifndef BOWWEAPONFactory_H
#define BOWWEAPONFABRIC_H

#include "weaponfactory.h"

#include "Atributes/Weapon/bow.h"


class BowWeaponFactory : public WeaponFactory
{
public:
    virtual std::shared_ptr<Weapon> createWeapon() const override;
};

#endif // BOWWEAPONFactory_H
