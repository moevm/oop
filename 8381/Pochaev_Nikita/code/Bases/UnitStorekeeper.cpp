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
