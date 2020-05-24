#pragma once

#include "GameDestroyer.h"
#include "GameMediator.h"
#include "GameFacade.h"

#include <vector>
#include <map>
#include <queue>
#include <memory>

#include "Field/Field.h"
#include "Neutrals/NeutralContext.h"
#include "Log/LogAdapter.h"

class ModifiedScene;
class Player;
class NeutralPlayer;


class Game
{
    friend class GameDestroyer;
    friend class GameMediator;
    friend class GameFacade;
    friend class GameCommand;

public:
    class Saver;
    class Loader;

    static Game& getInstance();

    int save(std::string& fileName);
    int load(std::string& fileName);

    bool exist();

    GameMediator& getGameMediator();
    GameFacade& getGameFacade();

    void objectWasCreated(Object* object);
    void objectWasDestructed(Object* object);
    void unitWasMoved(IUnit* unit);

    LogAdapter& getLogAdapter();

private:
    Game();
    Game(const Game& game) = delete;
    Game(Game&& game) = delete;
    ~Game();

    Player* getPlayerOfColor(uint16_t color);

    void unitWasCreated(IUnit* unit);
    void unitWasDestructed(IUnit* unit);
    void baseWasDestructed(Base* base);

    void turn();


    static Game* instance;
    static GameDestroyer destroyer;

    GameMediator* gameMediator;
    GameFacade* gameFacade;

    Field* field;

    std::vector <Player*> playerVector;
    NeutralPlayer* neutralPlayer;

    LogAdapter* logAdapter;
};


class Game::Saver {
public:
    Saver(std::string& fileName);
    Saver(const Saver& saver) = delete;
    Saver(Saver&& saver) = delete;
    ~Saver();
    int save(Game& game);

private:
    std::ofstream stream;
};


class Game::Loader {
public:
    Loader(std::string& fileName);
    Loader(const Loader& loader) = delete;
    Loader(Loader&& loader) = delete;
    ~Loader();
    int load(Game& game);

private:
    void clearAfterError(Game& game);

    std::ifstream stream;
};
