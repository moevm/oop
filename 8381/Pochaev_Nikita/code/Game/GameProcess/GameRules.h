#ifndef IGAMERULES_H
#define IGAMERULES_H

#include <cstddef>

#define ONE_TO_ONE_RULE_STEP 40
#define ONE_TO_ONE_RULE_FIELD 8
#define ONE_TO_ONE_RULE_PLAYERS 2

#define TWO_BY_TWO_RULE_STEP 20
#define TWO_BY_TWO_RULE_FIELD 15
#define TWO_BY_TWO_RULE_PLAYERS 4

enum GAME_RULES_TYPE
{
    NO_TYPE,
    ONE_TO_ONE,
    TWO_BY_TWO
};

class IGameRule
{
public:
    virtual ~IGameRule() = default;
    virtual size_t getStepTime() = 0;
    virtual size_t getFieldSize() = 0;
    virtual GAME_RULES_TYPE getType() = 0;
    virtual size_t getPlayersCount() = 0;
};

class AbstractGameRule : public IGameRule
{
public:
    ~AbstractGameRule() override = default;
    /**
     * @brief getStepTime
     * In seconds
     * @return
     */
    size_t getStepTime() override;
    size_t getFieldSize() override;
    size_t getPlayersCount() override;
    GAME_RULES_TYPE getType() override;

protected:
    size_t stepTime;
    size_t fieldSize;
    size_t playersCount;
};

class oneToOneRule : public AbstractGameRule
{
public:
    oneToOneRule();
    GAME_RULES_TYPE getType() override;
};

class twoByTwoRule : public AbstractGameRule
{
public:
    twoByTwoRule();
    GAME_RULES_TYPE getType() override;
};

#endif // IGAMERULES_H
