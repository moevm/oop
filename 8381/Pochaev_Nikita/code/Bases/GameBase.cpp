#include "GameBase.h"
#include "AuxiliaryFunctionality/TextColoring.h"

void GameBase::describeYourself()
{
    std::cout << ANSIColor::coloredString("I'm empty abstract base!",
            ANSIColor::FG_RED) << std::endl;
}

std::string GameBase::getInformationAbout()
{
    return "I'm empty abstract base!";
}

std::shared_ptr<CompositeUnit> GameBase::createLegion()
{
    auto legion = std::make_shared<CompositeUnit>();

    for(size_t i = 0; i < CANNON_FODDER_LEGION_Q; i++)
    {
        legion->addUnit(unitFabric.create(eUnitsType::CANNON_FODDER));
    }
    unitCount->increaseElementCount(eUnitsType::CANNON_FODDER, CANNON_FODDER_LEGION_Q);

    for(size_t i = 0; i < INFANTRY_LEGION_Q; i++)
    {
        legion->addUnit(unitFabric.create(eUnitsType::INFANTRY));
    }
    unitCount->increaseElementCount(eUnitsType::INFANTRY, INFANTRY_LEGION_Q);

    for(size_t i = 0; i < CAVALRY_LEGION_Q; i++)
    {
        legion->addUnit(unitFabric.create(eUnitsType::CAVALRY));
    }
    unitCount->increaseElementCount(eUnitsType::CAVALRY, CAVALRY_LEGION_Q);
    army.push_back(legion);

    return legion;
}

std::shared_ptr<CompositeUnit> GameBase::createSquad(eUnitsType type, size_t quantity)
{
    auto squad = std::make_shared<CompositeUnit>();
    if(!unitCount->checkAvailableSpace(type, quantity))
    {
        throw std::invalid_argument("Base limit of unit type: " + EnumTostring::enumToString(type) + " reached");
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
    unitCount->addUnitType(eUnitsType::CANNON_FODDER, CANNON_FODDER_MAX_QUANTITY);
    unitCount->addUnitType(eUnitsType::INFANTRY, INFANTRY_MAX_QUANTITY);
    unitCount->addUnitType(eUnitsType::SHOOTER, SHOOTER_MAX_QUANTITY);
    unitCount->addUnitType(eUnitsType::WIZARD, WIZARD_MAX_QUANTITY);
    unitCount->addUnitType(eUnitsType::CAVALRY, CAVALRY_MAX_QUANTITY);
}

void GameBase::updateAfterDeath(std::shared_ptr<Unit> corpse, [[maybe_unused]] size_t x, [[maybe_unused]] size_t y)
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

std::shared_ptr<Unit> GameBase::getUnit(eUnitsType typeID)
{
    std::shared_ptr<Unit> newUnit = unitFabric.create(typeID);
    unitCount->increaseElementCount(typeID, 1);
    newUnit->registerObserver(shared_from_this());
    return newUnit;
}

size_t GameBase::getHealth()
{
    return health;
}

std::string GameBase::getUnitCountInf()
{
    return unitCount->getTotalInformation();
}

std::string GameBase::convertEnumBaseNameToStr(eBaseType type)
{
    if(type == HUMAN_BASE)
    {
        return "human base";
    }
    else if(type == HELL_BASE)
    {
        return "hell base";
    }

    return "";
}

std::shared_ptr<BaseParametersCaretaker> GameBase::createMemento()
{
    std::shared_ptr<BaseParametersCaretaker> memento = std::make_shared<BaseParametersCaretaker>();

    memento->health = health;
    memento->type = getBaseType();
    memento->unitCountsData = unitCount->createMemento();

    return memento;
}

void GameBase::restoreMemento(std::shared_ptr<BaseParametersCaretaker> memento)
{
    health = memento->health;
    unitCount->restoreMemento(memento->unitCountsData);
}

eBaseType GameBase::getBaseType()
{
    return NONE_BASE;
}
