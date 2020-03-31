#include "Landscape.h"

bool Landscape::isAccessibleForMove(std::shared_ptr <Unit> &unit)
{
    if(std::find(movingUnitsProhibition.begin(),
            movingUnitsProhibition.end(), unit->getType()) != movingUnitsProhibition.end())
    {
        return false;
    }
    else if(std::find(actionTokensUnitsBoost.begin(),
                 actionTokensUnitsBoost.end(), unit->getType()) != actionTokensUnitsBoost.end())
    {
        unit->setExtraActionToken();
    }

    return true;
}

bool Landscape::isAccessibleForAttack(eUnitsType unitType)
{
    return !(std::find(attackUnitsProhibition.begin(),
                       attackUnitsProhibition.end(), unitType) != attackUnitsProhibition.end());
}
