#include "playerlog.hpp"

std::string PlayerLog::createUnit(bool isCreate, PLAYER player)
{
    std::string result = getPlayer(player);
    if (!isCreate) {
        result += "Unit wasn't create!";
        return result;
    }

    result += "Unit was create";

    return result;
}


std::string PlayerLog::attack(PLAYER player)
{
    std::string result = getPlayer(player);
    result += "Now is attacking.";
    return result;
}


std::string PlayerLog::deffend(PLAYER player)
{
    std::string result = getPlayer(player);
    result += "Now is deffending.";
    return result;
}


std::string PlayerLog::getPlayer(PLAYER player)
{
    if (player == PLAYER::ONE) {
        return "Player: 1. ";
    }

    return "Player: 2. ";
}
