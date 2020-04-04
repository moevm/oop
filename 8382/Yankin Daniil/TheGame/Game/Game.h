#pragma once

#include "GameDestroyer.h"
#include "GameMediator.h"
#include "GameFacade.h"

#include <vector>
#include <map>
#include <queue>

#include "Field/Field.h"
#include "Player/Player.h"
#include "Player/NeutralPlayer.h"
#include "Neutrals/NeutralContext.h"

class ModifiedScene;


class Game
{
    friend class GameDestroyer;
    friend class GameMediator;
    friend class GameFacade;
    friend class GameCommand;

public:
    static Game& getInstance();

    bool initializeByFile(char* filename);

    GameMediator& getGameMediator();
    GameFacade& getGameFacade();

    void objectWasCreated(Object* object);
    void objectWasDestructed(Object* object);
    void unitWasMoved(IUnit* unit);

private:
    Game();
    ~Game();

    Player* getPlayerOfColor(uint8_t color);

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
};
