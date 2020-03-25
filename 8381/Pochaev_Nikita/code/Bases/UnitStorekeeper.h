#ifndef OOP_UNITSTOREKEEPER_H
#define OOP_UNITSTOREKEEPER_H

#include <cstddef>
#include <map>
#include <memory>

#include "../Information headers/unitPar.h"
#include "../Auxiliary functionality/EnumToString.h"

/**
 * Contain current and max county of unit
 */
struct MaxCurrUnitQuantity
{
    MaxCurrUnitQuantity() = default;
    explicit MaxCurrUnitQuantity(size_t max) : maxCount(max) { };
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

private:
    /*
     * First par - name of unit (also using in fabric)
     */
    std::map<eUnitsType, MaxCurrUnitQuantity> unitInfo;
};

#endif //OOP_UNITSTOREKEEPER_H
