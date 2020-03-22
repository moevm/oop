#include "GameBase.h"
#include "../Auxiliary functionality/TextColoring.h"

void GameBase::describeYourself()
{
    std::cout << ANSIColor::coloredString("I'm empty abstract base!",
            ANSIColor::FG_RED) << std::endl;
}

std::shared_ptr<CompositeUnit> GameBase::createLegion()
{
    auto legion = std::make_shared<CompositeUnit>();

    for(size_t i = 0; i < CANNON_FODDER_LEGION_Q; i++)
    {
        legion->addUnit(unitFabric.create("Cannon fodder"));
    }
    unitCount->increaseElementCount("Cannon Fodder", CANNON_FODDER_LEGION_Q);

    for(size_t i = 0; i < INFANTRY_LEGION_Q; i++)
    {
        legion->addUnit(unitFabric.create("Infantry"));
    }
    unitCount->increaseElementCount("Infantry", INFANTRY_LEGION_Q);

    for(size_t i = 0; i < CAVALRY_LEGION_Q; i++)
    {
        legion->addUnit(unitFabric.create("Cavalry"));
    }
    unitCount->increaseElementCount("Cavalry", CAVALRY_LEGION_Q);
    army.push_back(legion);

    return legion;
}

std::shared_ptr<CompositeUnit> GameBase::createSquad(const std::string &type, size_t quantity)
{
    auto squad = std::make_shared<CompositeUnit>();
    if(!unitCount->checkAvailableSpace(type, quantity))
    {
        throw std::invalid_argument("Base limit of unit type: " + type + " reached");
    }

    for(size_t i = 0; i < quantity; i++)
    {
        std::shared_ptr<Unit> testUnit = unitFabric.create(type);
        squad->addUnit(unitFabric.create(type));
    }
    unitCount->increaseElementCount(type, quantity);
    army.push_back(squad);

    return squad;
}

void GameBase::initUnitCount()
{
    unitCount = std::make_unique<UnitStorekeeper>();
    unitCount->addUnitType("Cannon Fodder", CANNON_FODDER_MAX_QUANTITY);
    unitCount->addUnitType("Infantry", INFANTRY_MAX_QUANTITY);
    unitCount->addUnitType("Shooter", SHOOTER_MAX_QUANTITY);
    unitCount->addUnitType("Wizard", WIZARD_MAX_QUANTITY);
    unitCount->addUnitType("Cavalry", CAVALRY_MAX_QUANTITY);
}

void GameBase::updateAfterDeath(std::shared_ptr<Unit> corpse, size_t x, size_t y)
{
    // Write information about corpses into account
    if(corpse->isComposite())
    {
        unitCount->decreaseElementsCount(corpse->getComposition());
    }
    else
    {
        unitCount->decreaseOneElement(corpse->getType());
    }

    // Throw the corpse out of the army
    auto iterator = std::find(army.begin(), army.end(), corpse);
    if (iterator != army.end())
    {
        army.erase(iterator);
    }
}

std::shared_ptr<Unit> GameBase::getUnit(const std::string &typeID)
{
    std::shared_ptr<Unit> newUnit = unitFabric.create(typeID);
    unitCount->increaseElementCount(typeID, 1);
    newUnit->registerObserver(shared_from_this());
    return newUnit;
}
