#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <memory>
#include <QObject>

#include "Game/game.h"
#include "Game/GameProcess/GamersState.h"

class IGameProcess
{
public:
    virtual ~IGameProcess() = default;
    virtual std::shared_ptr<Game> getCurrGameInstance() = 0;

    virtual void delCurrGame() = 0;

    // proxy functionality for game class
    virtual size_t getPlayersCount() = 0;
    virtual std::shared_ptr<GameFieldProxy> getField() const = 0;
    virtual void createBase(eBaseType type, size_t xCoord, size_t yCoord, QString name) = 0;
    virtual bool getBaseCoordsByName(QString sourceBaseName, Coords &coords) = 0;
    virtual void restoreMemento(std::shared_ptr<GameParametersMemento> memento) = 0;
};

class SignalSlotGameProcess : public QObject
{
    Q_OBJECT

public:
    virtual ~SignalSlotGameProcess() = default;
    explicit SignalSlotGameProcess(QObject *parent = 0) :
        QObject(parent) {}
};

/**
 * @brief The GameProcess class
 * Machine in "State" pattern
 */
template<class Rule, typename PlayersCount>
class GameProcess :
        public std::enable_shared_from_this<GameProcess<Rule, PlayersCount>>,
            public SignalSlotGameProcess,
                public IGameProcess
{
private:
    GameProcess(size_t fieldSize, PlayersCount playersCount_, bool fill)
    {
        game = std::make_shared<Game>(fieldSize, playersCount_, fill);
        rule = std::make_unique<Rule>();
    }

    GameProcess(const GameProcess&);
    GameProcess(GameProcess&&);
    GameProcess& operator= (const GameProcess&);
    GameProcess& operator= (GameProcess&&);

    // Variables
    static std::shared_ptr<GameProcess> pInstance;
    std::shared_ptr<Game> game;
    std::unique_ptr<Rule> rule;
    PlayersCount playersCount{};
    std::shared_ptr<PlayerGameState> currState{};

public:
    ~GameProcess() = default;
    static std::shared_ptr<GameProcess> getInstance(size_t fieldSize, size_t playersCount_, bool fill)
    {
        if(!pInstance)
        {
            pInstance = std::make_shared<GameProcess>(fieldSize, playersCount_, fill);
        }

        return pInstance;
    }

    void delCurrGame() override
    {
        game = nullptr;
    }

    void setCurrState(std::shared_ptr<PlayerGameState> state)
    {
        currState = std::move(state);
    }

    size_t getPlayersCount() override
    {
        return game->getPlayersCount();
    }

    std::shared_ptr<GameFieldProxy> getField() const override
    {
        return game->getField();
    }

    void createBase(eBaseType type, size_t xCoord, size_t yCoord, QString name) override
    {
        game->createBase(type, xCoord, yCoord, name);
    }

    std::shared_ptr<Game> getCurrGameInstance() override
    {
        return game;
    }

    void restoreMemento(std::shared_ptr<GameParametersMemento> memento) override
    {
        game->restoreMemento(memento);
    }
};

#endif // GAMEPROCESS_H
