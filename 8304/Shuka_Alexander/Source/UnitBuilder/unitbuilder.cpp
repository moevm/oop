#include "unitbuilder.h"

using namespace unit;


UnitBuilder::UnitBuilder(const Point2D& point) : point(point)
{

}


void UnitBuilder::reset()
{
    unitFactory.reset();
    weaponFactory.reset();
    armorFactory.reset();
}


void UnitBuilder::setArmorFactory(std::shared_ptr<ArmorFactory> armorFactory)
{
    this->armorFactory = armorFactory;
}


void UnitBuilder::setMediator(std::shared_ptr<Mediator> mediator)
{
    this->mediator = mediator;
}


void UnitBuilder::setWeaponFactory(std::shared_ptr<WeaponFactory> weaponFactory)
{
    this->weaponFactory = weaponFactory;
}


void UnitBuilder::setUnitFactory(std::shared_ptr<UnitFactory> unitFactory)
{
    this->unitFactory = unitFactory;
}


void UnitBuilder::setPosition(const Point2D& point)
{
    this->point = point;
}


std::shared_ptr<Unit> UnitBuilder::getUnit()
{
    std::shared_ptr<Unit> unit = unitFactory->createUnit(point, mediator);
    unit->setArmor(armorFactory->createArmor());
    unit->setWeapon(weaponFactory->createWeapon());

    return unit;
}
