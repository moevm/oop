#include "unitcreator.hpp"


std::shared_ptr<Unit> UnitCreator::createSwordMan(const Position2D& position,std::shared_ptr<Mediator> mediator)
{
    UnitBuilder builder(position);

    std::unique_ptr<UnitFactory> unitFactory(new SwordManFactory);
    std::unique_ptr<ArmorFactory> armorFactory(new MediumArmorFactory);
    std::unique_ptr<WeaponFactory> weaponFactory(new SwordWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));
    builder.setMediator(mediator);

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitCreator::createSpearMan(const Position2D& position,std::shared_ptr<Mediator> mediator)
{
    UnitBuilder builder(position);

    std::unique_ptr<UnitFactory> unitFactory(new SpearManFactory);
    std::unique_ptr<ArmorFactory> armorFactory(new MediumArmorFactory);
    std::unique_ptr<WeaponFactory> weaponFactory(new SpearWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));
    builder.setMediator(mediator);

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitCreator::createArcher(const Position2D& position,std::shared_ptr<Mediator> mediator)
{
    UnitBuilder builder(position);

    std::unique_ptr<UnitFactory> unitFactory(new ArcherFactory);
    std::unique_ptr<ArmorFactory> armorFactory(new LightArmorFactory);
    std::unique_ptr<WeaponFactory> weaponFactory(new ArrowWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));
    builder.setMediator(mediator);

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitCreator:: createBallistic(const Position2D& position,std::shared_ptr<Mediator> mediator)
{
    UnitBuilder builder(position);

    std::unique_ptr<UnitFactory> unitFactory(new BallisticFactory);
    std::unique_ptr<ArmorFactory> armorFactory(new HeavyArmorFactory);
    std::unique_ptr<WeaponFactory> weaponFactory(new BallisticWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));
    builder.setMediator(mediator);

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitCreator::createVampire(const Position2D& position,std::shared_ptr<Mediator> mediator)
{
    UnitBuilder builder(position);

    std::unique_ptr<UnitFactory> unitFactory(new VampireFactory);
    std::unique_ptr<ArmorFactory> armorFactory(new HeavyArmorFactory);
    std::unique_ptr<WeaponFactory> weaponFactory(new VampireTeethWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));
    builder.setMediator(mediator);

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitCreator::createDragon(const Position2D& position,std::shared_ptr<Mediator> mediator)
{
    UnitBuilder builder(position);

    std::unique_ptr<UnitFactory> unitFactory(new DragonFactory);
    std::unique_ptr<ArmorFactory> armorFactory(new HeavyArmorFactory);
    std::unique_ptr<WeaponFactory> weaponFactory(new DragonFireWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));
    builder.setMediator(mediator);

    return  builder.getUnit();
}
