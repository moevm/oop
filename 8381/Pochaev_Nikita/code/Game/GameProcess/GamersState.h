#ifndef GAMERSSTATE_H
#define GAMERSSTATE_H

#include <cstddef>
#include <memory>

class IGameProcess;

class IGamersState
{
public:
    virtual ~IGamersState();
    virtual void passTheMove(std::shared_ptr<IGameProcess> machine) = 0;
    virtual void addBase() = 0;
};

class PlayerGameState : public IGamersState
{
public:
    void addBase() override;

protected:
    size_t baseCount{};
    int stepCount{};
};

#endif // GAMERSSTATE_H
