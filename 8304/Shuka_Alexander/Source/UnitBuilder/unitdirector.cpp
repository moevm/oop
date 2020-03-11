#include "unitdirector.h"


std::shared_ptr<Unit> UnitDirector::createDragon(const Point2D& point)
{
    UnitBuilder builder(point);

    std::unique_ptr<UnitFactory> unitFactory(new DragonFactory);
    std::unique_ptr<ArmorFactory> armorFactory(new MediumArmorFactory);
    std::unique_ptr<WeaponFactory> weaponFactory(new MagicWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitDirector::createThief(const Point2D& point)
{
    UnitBuilder builder(point);

    std::unique_ptr<UnitFactory> unitFactory(new ThiefFactory);
    std::unique_ptr<ArmorFactory> armorFactory(new NoArmorFactory);
    std::unique_ptr<WeaponFactory> weaponFactory(new SwordWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitDirector::createWarrior(const Point2D& point)
{
    UnitBuilder builder(point);

    std::unique_ptr<UnitFactory> unitFactory(new WarriorFactory);
    std::unique_ptr<ArmorFactory> armorFactory(new LightArmorFactory);
    std::unique_ptr<WeaponFactory> weaponFactory(new SwordWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));
    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitDirector::createTower(const Point2D& point)
{
    UnitBuilder builder(point);

    std::unique_ptr<UnitFactory> unitFactory(new TowerFactory);
    std::unique_ptr<ArmorFactory> armorFactory(new MediumArmorFactory);
    std::unique_ptr<WeaponFactory> weaponFactory(new BowWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitDirector::createKamikadze(const Point2D& point)
{
    UnitBuilder builder(point);

    std::unique_ptr<UnitFactory> unitFactory(new KamikadzeFactory);
    std::unique_ptr<ArmorFactory> armorFactory(new HeavyArmorFactory);
    std::unique_ptr<WeaponFactory> weaponFactory(new MagicWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));

    return  builder.getUnit();
}


std::shared_ptr<Unit> UnitDirector::createGoldMiner(const Point2D& point)
{
    UnitBuilder builder(point);

    std::unique_ptr<UnitFactory> unitFactory(new GoldMinerFactory);
    std::unique_ptr<ArmorFactory> armorFactory(new NoArmorFactory);
    std::unique_ptr<WeaponFactory> weaponFactory(new NoWeaponFactory);

    builder.setUnitFactory(std::move(unitFactory));
    builder.setArmorFactory(std::move(armorFactory));
    builder.setWeaponFactory(std::move(weaponFactory));

    return  builder.getUnit();
}
