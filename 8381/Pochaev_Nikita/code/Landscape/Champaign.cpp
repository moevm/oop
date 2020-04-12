#include "Champaign.h"

Champaign::Champaign()
{
    actionTokensUnitsBoost.emplace_back(eUnitsType::CAVALRY);
}

std::string Champaign::getNameOfLandscape()
{
    return "Champaign";
}
