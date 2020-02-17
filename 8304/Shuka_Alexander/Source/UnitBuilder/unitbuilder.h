#ifndef UNITBUILDER_H
#define UNITBUILDER_H


#include <memory>

#include "Unit/unit.h"

#include "Factory/ArmorFactory/armorfactory.h"
#include "Factory/WeaponFactory/weaponfactory.h"
#include "Factory/UnitFactory/unitfactory.h"


class UnitBuilder
{
public:
    UnitBuilder(const Point2D& point);
    void reset();

    void setArmorFactory(std::unique_ptr<ArmorFactory> armorFactory);
    void setWeaponFactory(std::unique_ptr<WeaponFactory> weaponFactory);
    void setUnitFactory(std::unique_ptr<UnitFactory> unitFactory);
    void setPosition(const Point2D& point);

    std::shared_ptr<Unit> getUnit();

private:
    std::unique_ptr<UnitFactory> unitFactory;
    std::unique_ptr<WeaponFactory> weaponFactory;
    std::unique_ptr<ArmorFactory> armorFactory;
    Point2D point;
};

#endif // UNITBUILDER_H
