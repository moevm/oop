#ifndef OOP_UNITSTOREKEEPER_H
#define OOP_UNITSTOREKEEPER_H

#include <cstddef>
#include <map>
#include <memory>

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
    bool checkAvailableSpace(const std::string& type, size_t toAdd);
    bool increaseElementCount(const std::string& type, size_t toAdd);
    void addUnitType(const std::string& type, size_t maxCount);
    void decreaseElementsCount(const std::map<std::string, size_t>& decreasingUnits);
    void decreaseOneElement(const std::string& unitType);
    std::string getTotalInformation();

private:
    /*
     * First par - name of unit (also using in fabric)
     */
    std::map<std::string, MaxCurrUnitQuantity> unitInfo;
};

#endif //OOP_UNITSTOREKEEPER_H
