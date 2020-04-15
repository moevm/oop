#ifndef OOP_LANDSCAPE_H
#define OOP_LANDSCAPE_H

#include "Units/Unit.h"

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

/**
 * If unit stand on cell with landscape move boost
 */
class Landscape
{
public:
    Landscape() = default;
    virtual ~Landscape() = default;

    // It can also make a boost or vice versa
    virtual bool isAccessibleForMove(std::shared_ptr<Unit> &unit);
    virtual bool isAccessibleForAttack(eUnitsType unitType);

    virtual std::string getNameOfLandscape() = 0;

protected:
    std::string type;
    std::vector<eUnitsType> movingUnitsProhibition;
    std::vector<eUnitsType> actionTokensUnitsBoost;
    std::vector<eUnitsType> attackUnitsProhibition;
};

#endif //OOP_LANDSCAPE_H
