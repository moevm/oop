#include "GameRoomState.hpp"

bool GameRoomState::checkPermission(std::string playerID)
{
    return nowPlayer ? playerID == nowPlayer->getPlayerID() : false;
}