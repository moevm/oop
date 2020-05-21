#ifndef GAMERSSTATE_H
#define GAMERSSTATE_H

#include <cstddef>
#include <memory>

class IGameProcess;

class IGamersState
{
public:
    virtual ~IGamersState() = default;
    virtual void initNextState(std::shared_ptr<IGamersState> nextState) = 0;
    virtual std::shared_ptr<IGamersState> passTheMove() = 0;
    virtual void addBase() = 0;
    virtual size_t getPlayerNumb() = 0;
    virtual size_t getBaseCount() = 0;
};

class PlayerGameState : public IGamersState
{
public:
    ~PlayerGameState() override = default;
    PlayerGameState(size_t playerNumber_);
    void initNextState(std::shared_ptr<IGamersState> nextState) override;
    void addBase() override;
    std::shared_ptr<IGamersState> passTheMove() override;
    size_t getPlayerNumb() override;
    size_t getBaseCount() override;

private:
    size_t playerNumber{};
    size_t baseCount{};
    int stepCount{};

    std::shared_ptr<IGamersState> nextPlayerState;
};

#endif // GAMERSSTATE_H
