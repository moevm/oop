#include <ostream>
#include "UnitStorekeeper.h"

bool UnitStorekeeper::checkAvailableSpace(eUnitsType type, size_t toAdd)
{
    return unitInfo[type].currCount + toAdd <= unitInfo[type].maxCount;
}

bool UnitStorekeeper::increaseElementCount(eUnitsType type, size_t toAdd)
{
    if(unitInfo[type].currCount + toAdd > unitInfo[type].maxCount)
    {
        return false;
    } else
    {
        unitInfo[type].currCount += toAdd;
        return true;
    }
}

void UnitStorekeeper::addUnitType(eUnitsType type, size_t maxCount)
{
    unitInfo.insert(std::pair<eUnitsType, MaxCurrUnitQuantity>(type, maxCount));
    //unitInfo[type] = MaxCurrUnitQuantity(maxCount);
}

std::string UnitStorekeeper::getTotalInformation()
{
    std::string result = "Current base control following units.\n";
    for (const auto& x: unitInfo)
    {
        result.append(EnumTostring::enumToString(x.first) + ": " + std::to_string(x.second.currCount) + ";\n");
    }

    return result;
}

void UnitStorekeeper::decreaseElementsCount(const std::map<eUnitsType, size_t> &decreasingUnits)
{
    for (const auto &curr : decreasingUnits)
    {
        unitInfo[curr.first].currCount -= curr.second;
    }
}

void UnitStorekeeper::decreaseOneElement(eUnitsType unitType)
{
    unitInfo[unitType].currCount--;
}

std::shared_ptr<UnitStorekeeperParametersMemento> UnitStorekeeper::createMemento()
{
    std::shared_ptr<UnitStorekeeperParametersMemento> memento = std::make_unique<UnitStorekeeperParametersMemento>();

    std::map<eUnitsType, MaxCurrUnitQuantity>::iterator iter;
    for(iter = unitInfo.begin(); iter != unitInfo.end(); iter++)
    {
        memento->unitAccountingInf.push_back(std::to_string(iter->first) + " : " + std::to_string(iter->second.maxCount) + ";" + std::to_string(iter->second.currCount));
    }

    return memento;
}

void UnitStorekeeper::restoreMemento(std::shared_ptr<UnitStorekeeperParametersMemento> memento)
{
    const std::regex pattern("(\\d)\\s:\\s(\\d*);(\\d*)");

    for(const auto &curr : memento->unitAccountingInf)
    {
        std::smatch match;
        if(std::regex_search(curr, match, pattern))
        {
            unitInfo.insert(std::pair(static_cast<eUnitsType>(atoi(match[1].str().c_str())), MaxCurrUnitQuantity(atoi(match[2].str().c_str()), atoi(match[3].str().c_str()))));
        }
    }
}
