#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

/*
 * Singleton info:
 * https://habr.com/ru/post/455848/
 *
 * About singleton:
 * https://tproger.ru/translations/singleton-pitfalls/
 */

#include <memory>
#include <QObject>
#include <QMessageBox>

#include "Game/game.h"
#include "Game/GameProcess/GamersState.h"
#include "Game/GameProcess/GameRules.h"

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

    virtual void updateResults() = 0;

public slots:
    void on_passMove_button_clicked();

signals:
    void setCurrentPlayerNumber(size_t numb);

protected:
    std::shared_ptr<IGamersState> currentState;
};

/**
 * @brief The GameProcess class
 * Machine in "State" pattern
 */
template<class Rule, typename PlayersCount>
class GameProcess :
    public SignalSlotGameProcess,
        public IGameProcess
{
public:
    GameProcess(const GameProcess&) = delete;
    GameProcess(GameProcess&&) = delete;
    GameProcess& operator= (const GameProcess&) = delete;
    GameProcess& operator= (GameProcess&&) = delete;

private:
    GameProcess(size_t fieldSize, PlayersCount playersCount_, bool fill, GAME_RULES_TYPE type)
    {
        if(type == ONE_TO_ONE)
        {
            rule = std::make_shared<oneToOneRule>();
        }
        else if (type == TWO_BY_TWO)
        {
            rule = std::make_shared<twoByTwoRule>();
        }
        game = std::make_shared<Game>(fieldSize, fieldSize, playersCount_, fill);

        // init states
        states.reserve(playersCount_);
        for(int i = 0; i < static_cast<int>(playersCount_); ++i)
        {
            states.push_back(std::make_shared<PlayerGameState>(i));
        }
        for(int i = 0; i < static_cast<int>(playersCount_) - 1; ++i)
        {
            states[i]->initNextState(states[i + 1]);
        }
        states[states.size() - 1]->initNextState(states[0]);
        currentState = states[0];
    }

    // Variables
    std::shared_ptr<Game> game;
    PlayersCount playersCount{};
    std::shared_ptr<Rule> rule;

    std::vector<std::shared_ptr<IGamersState>> states;

public:
    ~GameProcess() = default;

    template<class RuleInst, typename PlayersCountInst>
    static std::weak_ptr<GameProcess> getInstance(size_t fieldSize, size_t playersCount_, bool fill, GAME_RULES_TYPE type)
    {
        static auto pInstance = std::shared_ptr<GameProcess>(new GameProcess(fieldSize, playersCount_, fill, type));
        return pInstance;
    }

    void delCurrGame() override
    {
        game = nullptr;
    }

    void setCurrState(std::shared_ptr<PlayerGameState> state)
    {
        currentState = std::move(state);
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
        currentState->addBase();
        game->createBase(type, xCoord, yCoord, name);
    }

    std::shared_ptr<Game> getCurrGameInstance() override
    {
        return game;
    }

    bool getBaseCoordsByName(QString sourceBaseName, Coords &coords) override
    {
        return game->getBaseCoordsByName(sourceBaseName, coords);
    }

    void restoreMemento(std::shared_ptr<GameParametersMemento> memento) override
    {
        game->restoreMemento(memento);
    }

    void updateResults() override
    {
        if(rule == nullptr)
        {
            return;
        }
        std::shared_ptr<AbstractGameRule> currRule = std::dynamic_pointer_cast<AbstractGameRule>(rule);
        if(currRule->getType() != NO_TYPE && currentState->getPlayerNumb() == 0)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Game result");
            if(currRule->getType() == ONE_TO_ONE)
            {
                if(states[0]->getBaseCount() > states[1]->getBaseCount())
                {
                    msgBox.setText("Zero player won!");
                    msgBox.exec();
                }
                else if(states[0]->getBaseCount() < states[1]->getBaseCount())
                {
                    msgBox.setText("First player won!");
                    msgBox.exec();
                }
            }
            else if(currRule->getType() == TWO_BY_TWO)
            {
                if(states[0]->getBaseCount() == 0 && states[1]->getBaseCount() == 0)
                {
                    msgBox.setText("Zero command won!");
                    msgBox.exec();
                }
                else if(states[2]->getBaseCount() == 0 && states[3]->getBaseCount() == 0)
                {
                    msgBox.setText("First command won!");
                    msgBox.exec();
                }
            }
        }
    }
};

#endif // GAMEPROCESS_H
