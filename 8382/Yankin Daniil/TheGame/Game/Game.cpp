#include "Game.h"
#include "Field/Field.h"
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



Game::Game() {
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



bool Game::initializeByFile(char* filename) {
    // Для Game поле инициализируется лишь единожды
    // Один Game - одно поле. А Game всегда один!
    if (field != nullptr)
        return false;

    // Инициализация поля
    std::ifstream stream(filename);
    field = new Field(stream);

    std::vector<int> logParameters = {field->getWidth(), field->getHeight()};
    logAdapter->log(LOG_GAME_CREATED, logParameters);

    // Добавление игроков
    playerVector.push_back(new Player(PLAYER_BLUE));
    playerVector.push_back(new Player(PLAYER_RED));
    neutralPlayer = new NeutralPlayer();

    // Считывание объектов
    std::vector <std::vector <Base*>> baseVector;
    baseVector.resize(playerVector.size());

    while (!stream.eof()) {
        uint16_t objectType;
        uint16_t x;
        uint16_t y;

        stream >> objectType >> x >> y;

        // Это юниты
        if (objectType >= UNIT_SWORDSMAN && objectType <= UNIT_RAM) {
            uint16_t playerColor;
            stream >> playerColor;

            Player* player = getPlayerOfColor(playerColor);
            Point point(x, y);

            if (player != nullptr && field->isUnitFree(point)) {
                uint16_t baseNumber;
                stream >> baseNumber;

                if (baseNumber < baseVector[playerColor].size()) {
                    UnitFactory factory;
                    Unit* unit = factory.produce(objectType, point, baseVector[playerColor][baseNumber]);
                    field->setUnit(point, unit);
                }
            }
        }

        // А это базы
        else if (objectType == BASE) {
            uint16_t playerColor;
            stream >> playerColor;

            Player* player = getPlayerOfColor(playerColor);
            Point point(x, y);

            if (player != nullptr && field->isBuildingFree(point)) {
                Base* base = new Base(point, player);
                field->setBase(point, base);

                baseVector[playerColor].push_back(base);
            }
        }

        // А это нейтральные объекты
        else if (objectType == NEUT_OBJECT) {
            Point point(x, y);

            if (field->isBuildingFree(point)) {
                NeutralContext* context = new NeutralContext(Point(x, y), neutralPlayer);
                field->setContext(point, context);
            }
        }

        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    stream.close();

    // Конец считывания

    return true;
}



GameMediator& Game::getGameMediator() {
    return *gameMediator;
}

GameFacade& Game::getGameFacade() {
    return *gameFacade;
}



Player* Game::getPlayerOfColor(uint8_t color) {
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
