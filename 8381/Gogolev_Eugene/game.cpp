#include "game.hpp"
#include "units/infantries/swordsmen.hpp"
#include "units/infantries/spearmen.hpp"
#include "units/shooters/archers.hpp"
#include "units/shooters/crossbowman.hpp"
#include "units/cavalries/rider.hpp"
#include "units/cavalries/knight.hpp"
#include "units/citadel.hpp"
#include "units/neutrals/villager.hpp"
#include "units/neutrals/fair.hpp"
#include "units/neutrals/farmer.hpp"
#include "units/neutrals/sheep.hpp"
#include "loggers/terminal_logger.hpp"

Game::Game (GameRule* rule, UI* ui) {
    srand(time(nullptr));
    this->gameRule = rule;
    this->ui = ui;
    if (gameRule != nullptr) {
        gameRule->onGameStart(this);
        ui->init(sizeX, sizeY);
    }
}

Game::~Game () {
    delete tileMap;
}

bool Game::onField (int x, int y) {
    return !(x < 0 || y < 0 || x >= sizeX || y >= sizeY);
}

void Game::setSize (int sizeX, int sizeY) {
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    delete tileMap;
    int size = sizeX * sizeY;
    tileMap = new Tile* [size];
    for (int i = 0; i < size; i++) {
        tileMap[i] = &meadow;
    }

    if (ui != nullptr) {
        ui->init(sizeX, sizeY);
    }
}

int Game::getSizeX () const {
    return sizeX;
}

int Game::getSizeY () const {
    return sizeY;
}

void Game::setTile (int x, int y, char id) {
    setTile(x, y, getTile(id));
}

Tile* Game::getTile (int x, int y) {
    if (!onField(x, y)) return &water;
    return tileMap[toIndex(x, y)];
}

void Game::setLogger (Logger* logger) {
    delete this->logger;
    this->logger = logger;
}

void Game::setUI (UI* ui) {
    this->ui = ui;
    ui->init(sizeX, sizeY);
}

UI* Game::getUI () {
    return ui;
}

Logger& Game::getLogger () {
    if (logger == nullptr) {
        setLogger(new TerminalLogger());
    }
    return *logger;
}

Unit* Game::createUnit (string key) {
    if (unitMap.size() >= gameRule->getMaxUnits()) return nullptr;
    return registerUnit(createUnitInstance(key));
}

const vector<Unit*>* Game::findUnits (int x, int y, int radius) {
    cash.clear();
    int qrtRadius = radius * radius;
    for (auto& it : unitMap) {
        Unit* unit = it.second;
        if (unit->sqrDistanceTo(x, y) <= qrtRadius) {
            cash.push_back(unit);
        }
    }
    return &cash;
}

Unit* Game::findUnit (int id) {
    auto it = unitMap.find(id);
    if (it != unitMap.end()) {
        return it->second;
    }
    else {
        return nullptr;
    }
}

void Game::setTarget (Team team, int x, int y) {
    for (auto& it : unitMap) {
        if (it.second->getTeam() == team) it.second->setTargetXY(x, y);
    }
}

void Game::update () {
    for (auto& it : unitMap) {
        it.second->update();
    }

    if (ui != nullptr) {
        for (int x = 0; x < sizeX; x++) {
            for (int y = 0; y < sizeY; y++) {
                ui->displayTile(x, y, getTile(x, y));
            }
        }

        for (auto& it : unitMap) {
            ui->displayUnit(it.second);
        }
    }

    for (auto it = unitMap.begin(); it != unitMap.end();) {
        Unit* unit = it->second;
        if (unit->isDead()) {
            getLogger().log(unit->getType() + " " + to_string(unit->getId()) + " is dead");
            it = unitMap.erase(it);
            delete unit;
        }
        else {
            it++;
        }
    }

    gameRule->onGameUpdate();
}

int Game::toIndex (int x, int y) const {
    return y * sizeX + x;
}

Unit* Game::registerUnit (Unit* unit) {
    int id = nextId++;
    unit->onGameFieldEnter(id, this);
    unitMap[id] = unit;
    return unit;
}

Unit* Game::createUnitInstance (string key) {
    if (key == Swordsmen::type) {
        return new Swordsmen();
    }
    else if (key == Spearmen::type) {
        return new Spearmen();
    }
    else if (key == Archers::type) {
        return new Archers();
    }
    else if (key == Crossbowman::type) {
        return new Crossbowman();
    }
    else if (key == Rider::type) {
        return new Rider();
    }
    else if (key == Knight::type) {
        return new Knight();
    }
    else if (key == Citadel::type) {
        return new Citadel();
    }
    else if (key == Villager::type) {
        return new Villager();
    }
    else if (key == Fair::type) {
        return new Fair();
    }
    else if (key == Farmer::type) {
        return new Farmer();
    }
    else if (key == Sheep::type) {
        return new Sheep();
    }
    else {
        return nullptr;
    }

}

void Game::save (ostream& os) {
    os << nextId << ' ' << sizeX << ' ' << sizeY << endl;
    int size = sizeX * sizeY;
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            os << getTile(x, y)->getId() << ' ';
        }
        os << endl;
    }

    os << unitMap.size() << endl;
    for (auto& it : unitMap) {
        Unit* unit = it.second;
        os << unit->getType() << ' ' << unit->getId() << endl;
        unit->save(os);
    }
}

void Game::load (istream& is) {
    is >> nextId >> sizeX >> sizeY;
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            char id;
            is >> id;
            setTile(x, y, id);
        }
    }
    int count;
    is >> count;
    for (int i = 0; i < count; i++) {
        string type;
        int id;
        is >> type >> id;
        Unit* unit = createUnitInstance(type);
        unit->onGameFieldEnter(id, this);
        unit->load(is);
        unitMap[id] = unit;
    }
}

Tile* Game::getTile (char id) {
    switch (id) {
        case Meadow::id:
            return &meadow;
        case Fortress::id:
            return &fortress;
        case Water::id:
            return &water;
        default:
            throw out_of_range("Unknows tile id: " + to_string(id));
    }
}

void Game::setTile (int x, int y, Tile* tile) {
    tileMap[toIndex(x, y)] = tile;
}





