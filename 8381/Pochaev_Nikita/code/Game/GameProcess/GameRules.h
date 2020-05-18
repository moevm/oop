#ifndef IGAMERULES_H
#define IGAMERULES_H

#include <cstddef>

#define ONE_TO_ONE_RULE_STEP 40
#define ONE_TO_ONE_RULE_FIELD 8

#define TWO_BY_TWO_RULE_STEP 20
#define TWO_BY_TWO_RULE_FIELD 15

class IGameRule
{
public:
    virtual ~IGameRule() = 0;
    virtual size_t getStepTime() = 0;
    virtual size_t getFieldSize() = 0;
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

protected:
    size_t stepTime;
    size_t fieldSize;
};

class oneToOneRule : public AbstractGameRule
{
public:
    oneToOneRule();
};

class twoByTwoRule : public AbstractGameRule
{
public:
    twoByTwoRule();
};

#endif // IGAMERULES_H
