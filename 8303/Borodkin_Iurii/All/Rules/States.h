#ifndef STATES_H
#define STATES_H

#include "GameField.h"

class State
{
public:
    void setGameField(GameField*);
    virtual unsigned player() = 0;
    virtual bool stateObject(std::pair<size_t, size_t>);
    virtual ~State() = default;
private:
    GameField* gameField = nullptr;
};

class State1 : public State
{
public:
    unsigned player() override;
};

class State2 : public State
{
public:
    unsigned player() override;
};

class State3 : public State
{
public:
    unsigned player() override;
};

#endif // STATES_H
