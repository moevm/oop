#include "UnitStorekeeper.h"

bool UnitStorekeeper::checkAvailableSpace(const std::string& type, size_t toAdd)
{
    return unitInfo[type].currCount + toAdd <= unitInfo[type].maxCount;
}

bool UnitStorekeeper::increaseElementCount(const std::string& type, size_t toAdd)
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

void UnitStorekeeper::addUnitType(const std::string& type, size_t maxCount)
{
    unitInfo.insert(std::pair<std::string, MaxCurrUnitQuantity>(type, maxCount));
    //unitInfo[type] = MaxCurrUnitQuantity(maxCount);
}

std::string UnitStorekeeper::getTotalInformation()
{
    std::string result = "Current base control following units.\n";
    for (const auto& x: unitInfo)
    {
        result.append(x.first + ": " + std::to_string(x.second.currCount) + ";\n");
    }

    return result;
}

void UnitStorekeeper::decreaseElementsCount(const std::map<std::string, size_t>& decreasingUnits)
{
    for (const auto &curr : decreasingUnits)
    {
        unitInfo[curr.first].currCount -= curr.second;
    }
}

void UnitStorekeeper::decreaseOneElement(const std::string& unitType)
{
    unitInfo[unitType].currCount--;
}
