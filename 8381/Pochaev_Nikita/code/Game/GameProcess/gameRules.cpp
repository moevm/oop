#include "Game/GameProcess/GameRules.h"

size_t AbstractGameRule::getStepTime()
{
    return stepTime;
}

size_t AbstractGameRule::getFieldSize()
{
    return fieldSize;
}

oneToOneRule::oneToOneRule()
{
    stepTime = ONE_TO_ONE_RULE_STEP;
    fieldSize = ONE_TO_ONE_RULE_FIELD;
}

twoByTwoRule::twoByTwoRule()
{
    stepTime = TWO_BY_TWO_RULE_STEP;
    fieldSize = TWO_BY_TWO_RULE_FIELD;
}
