#include "unitbuilder.hpp"

UnitBuilder::UnitBuilder(const Position2D& position) : position(position)
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


void UnitBuilder::setMediator(std::shared_ptr<Mediator> mediator)
{
    this->mediator = mediator;
}


void UnitBuilder::setWeaponFactory(std::unique_ptr<WeaponFactory> weaponFactory)
{
    this->weaponFactory = std::move(weaponFactory);
}


void UnitBuilder::setUnitFactory(std::unique_ptr<UnitFactory> unitFactory)
{
    this->unitFactory = std::move(unitFactory);
}


void UnitBuilder::setPosition(const Position2D& position)
{
    this->position = position;
}


std::shared_ptr<Unit> UnitBuilder::getUnit()
{
    std::shared_ptr<Unit> unit = unitFactory->createUnit(position,mediator);
    unit->setArmor(armorFactory->createArmor());
    unit->setWeapon(weaponFactory->createWeapon());

    return unit;
}
