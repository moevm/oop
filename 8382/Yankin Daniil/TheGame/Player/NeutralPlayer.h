#pragma once

#include <cstdint>
#include <set>
#include "Game/Game.h"

class NeutralContext;


class NeutralPlayer
{
    friend class GameFacade;
    friend class Game::Saver;

public:
    ~NeutralPlayer();

    void addNeutralObject(NeutralContext* neutralObject);
    void removeNeutralObject(NeutralContext* neutralObject);

private:
    std::set <NeutralContext*>* getNeutralObjectSet();

    std::set <NeutralContext*> neutralSet;
};
