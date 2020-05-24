#include "Game.h"
#include "Field/Field.h"
#include "Player/Player.h"
#include "Player/NeutralPlayer.h"
#include "Unit/UnitHeader.h"
#include "Base/Base.h"
#include "Neutrals/NeutralContext.h"


Game* Game::instance = nullptr;
GameDestroyer Game::destroyer;


Game& Game::getInstance() {
    if (instance == nullptr) {
        instance = new Game();
        destroyer.init(instance);
    }
    return *instance;
}



Game::Game() : field(nullptr), neutralPlayer(nullptr) {
    gameMediator = new GameMediator(this);
    gameFacade = new GameFacade(this);
    field = nullptr;
    logAdapter = new LogAdapter(LOGGING_DIR_FILE, LOGGING_MODE_DEFAULT);
}

Game::~Game() {
    delete gameMediator;
    gameMediator = nullptr;

    for (auto player = playerVector.begin(); player != playerVector.end(); player++) {
        delete (*player);
    }
    delete neutralPlayer;
    delete field;
    delete gameFacade;

    std::vector<int> logParameters;
    logAdapter->log(LOG_GAME_DELETED, logParameters);
    delete logAdapter;
}

int Game::save(std::string& fileName) {
    if (field == nullptr) {
        return 2;
    }

    try {
        Game::Saver saver(fileName);
        return saver.save(*this);
    }
    catch(std::runtime_error error) {
        return 3;
    }
}

int Game::load(std::string& fileName) {
    gameFacade->clear();

    for (auto player = playerVector.begin(); player != playerVector.end(); player++) {
        delete (*player);
    }
    playerVector.clear();

    delete neutralPlayer;
    neutralPlayer = nullptr;

    delete field;
    field = nullptr;

    try {
        Game::Loader loader(fileName);
        return loader.load(*this);
    }
    catch(std::runtime_error error) {
        return 3;
    }
}

bool Game::exist() {
    if (field)
        return true;
    else
        return false;
}


GameMediator& Game::getGameMediator() {
    return *gameMediator;
}

GameFacade& Game::getGameFacade() {
    return *gameFacade;
}



Player* Game::getPlayerOfColor(uint16_t color) {
    for (auto iter = playerVector.begin(); iter != playerVector.end(); iter++) {
        if ((*iter)->getColor() == color) {
            return *iter;
        }
    }
    return nullptr;
}



void Game::objectWasCreated(Object* object) {
    if (object->getGroupType() == UNIT) {
        unitWasCreated(static_cast <Unit*> (object));
    }
}

void Game::unitWasCreated(IUnit* unit) {
    field->setUnit(unit->getPoint(), unit);
    gameFacade->setVisualUnitPos(unit);
}


void Game::objectWasDestructed(Object* object) {
    if (object->getGroupType() == UNIT) {
        unitWasDestructed(static_cast <IUnit*> (object));
    }
    else if (object->getGroupType() == BASE) {
        baseWasDestructed(static_cast <Base*> (object));
    }
}

void Game::unitWasDestructed(IUnit* unit) {
    field->removeUnit(unit->getPoint());
    gameFacade->unitWasDestructed(unit);
}

void Game::baseWasDestructed(Base* base) {
    field->removeBase(base->getPoint());
    gameFacade->baseWasDestructed(base);
}

void Game::unitWasMoved(IUnit* unit) {
    gameFacade->setVisualUnitPos(unit);
}



void Game::turn() {
    for (auto player = playerVector.begin(); player != playerVector.end(); player++) {
        std::set <IUnit*>* unitSet = (*player)->getUnitSet();
        for (auto unit = unitSet->begin(); unit != unitSet->end(); unit++) {
            (*unit)->smallHeal();
            (*unit)->renewMovePoints();
        }
    }
    std::vector<int> parameters;
    logAdapter->log(LOG_GAME_TURN, parameters);
}



LogAdapter& Game::getLogAdapter() {
    return *logAdapter;
}
