#include "Game/GameProcess/GameRules.h"

size_t AbstractGameRule::getStepTime()
{
    return stepTime;
}

size_t AbstractGameRule::getFieldSize()
{
    return fieldSize;
}

size_t AbstractGameRule::getPlayersCount()
{
    return playersCount;
}

GAME_RULES_TYPE AbstractGameRule::getType()
{
    return NO_TYPE;
}

oneToOneRule::oneToOneRule()
{
    stepTime = ONE_TO_ONE_RULE_STEP;
    fieldSize = ONE_TO_ONE_RULE_FIELD;
    playersCount = ONE_TO_ONE_RULE_PLAYERS;
}

twoByTwoRule::twoByTwoRule()
{
    stepTime = TWO_BY_TWO_RULE_STEP;
    fieldSize = TWO_BY_TWO_RULE_FIELD;
    playersCount = TWO_BY_TWO_RULE_PLAYERS;
}

GAME_RULES_TYPE oneToOneRule::getType()
{
    return ONE_TO_ONE;
}

GAME_RULES_TYPE twoByTwoRule::getType()
{
    return TWO_BY_TWO;
}
