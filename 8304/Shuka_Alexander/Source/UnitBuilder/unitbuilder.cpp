#include "unitbuilder.h"


UnitBuilder::UnitBuilder(const Point2D& point) : point(point)
{

}


void UnitBuilder::reset()
{
    unitFactory.reset();
    weaponFactory.reset();
    armorFactory.reset();
}


void UnitBuilder::setArmorFactory(std::unique_ptr<ArmorFactory> armorFactory)
{
    this->armorFactory = std::move(armorFactory);
}


void UnitBuilder::setWeaponFactory(std::unique_ptr<WeaponFactory> weaponFactory)
{
    this->weaponFactory = std::move(weaponFactory);
}


void UnitBuilder::setUnitFactory(std::unique_ptr<UnitFactory> unitFactory)
{
    this->unitFactory = std::move(unitFactory);
}


void UnitBuilder::setPosition(const Point2D& point)
{
    this->point = point;
}


std::shared_ptr<Unit> UnitBuilder::getUnit()
{
    std::shared_ptr<Unit> unit = unitFactory->createUnit(point);
    unit->setArmor(armorFactory->createArmor());
    unit->setWeapon(weaponFactory->createWeapon());

    return unit;
}
