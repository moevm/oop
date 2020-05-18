#ifndef OOP_UNITSTOREKEEPER_H
#define OOP_UNITSTOREKEEPER_H

#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <regex>
#include <algorithm>

#include "InformationHeaders/unitPar.h"
#include "AuxiliaryFunctionality/EnumToString.h"
#include "Game/Saving/SaveStuctures.h"

/**
 * Contain current and max county of unit
 */
struct MaxCurrUnitQuantity
{
    MaxCurrUnitQuantity() = default;
    explicit MaxCurrUnitQuantity(size_t max) : maxCount(max) { };
    MaxCurrUnitQuantity(size_t max, size_t curr) : maxCount(max), currCount(curr) { };

    size_t maxCount{};
    size_t currCount{};
};

/**
 * Save information about unit quantity
 */
class UnitStorekeeper
{
public:
    UnitStorekeeper() = default;
    ~UnitStorekeeper() = default;
    bool checkAvailableSpace(eUnitsType type, size_t toAdd);
    bool increaseElementCount(eUnitsType type, size_t toAdd);
    void addUnitType(eUnitsType type, size_t maxCount);
    void decreaseElementsCount(const std::map<eUnitsType, size_t>& decreasingUnits);
    void decreaseOneElement(eUnitsType unitType);
    std::string getTotalInformation();

    // Memento functionality
    std::shared_ptr<UnitStorekeeperParametersMemento> createMemento();
    void restoreMemento(std::shared_ptr<UnitStorekeeperParametersMemento> memento);

private:
    /*
     * First par - name of unit (also using in fabric)
     */
    std::map<eUnitsType, MaxCurrUnitQuantity> unitInfo;
};

#endif //OOP_UNITSTOREKEEPER_H
