#include "Game/GameProcess/GamersState.h"

PlayerGameState::PlayerGameState(size_t playerNumber_) : playerNumber(playerNumber_) { }

void PlayerGameState::initNextState(std::shared_ptr<IGamersState> nextState)
{
    nextPlayerState = std::move(nextState);
}

void PlayerGameState::addBase()
{
    baseCount++;
}

/**
 * @brief PlayerGameState::passTheMove
 * Return pointer to the next state
 */
std::shared_ptr<IGamersState> PlayerGameState::passTheMove()
{
    stepCount++;

    return nextPlayerState;
}

size_t PlayerGameState::getPlayerNumb()
{
    return playerNumber;
}

size_t PlayerGameState::getBaseCount()
{
    return baseCount;
}
