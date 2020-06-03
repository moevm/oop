#include "citadel.hpp"
#include "../exceptions/out_of_bounds_exception.hpp"

static const char sprite[3][3] = {{' ', '^', ' '},
                                  {'<', ' ', '>'},
                                  {' ', 'V', ' '}};

const string Citadel::type = "Citadel";

Citadel::Citadel () {
    hp = Citadel::getMaxHP();
}

int Citadel::getMaxHP () {
    return 50;
}

char Citadel::getChar (int x, int y) {
    validateChar(x, y);
    if (x == 1 && y == 1) {
        switch (team) {
            case RED:
                return 'A';
            case BLUE:
                return '0';
            default:
                return '?';
        }
    }
    if (y == 2) {
        switch (x) {
            case 0:
                return '0' + hp / 100 % 10;
                break;
            case 1:
                return '0' + hp / 10 % 10;
                break;
            case 2:
                return '0' + hp % 10;
                break;
        }
    }
    return sprite[y][x];
}

void Citadel::update () {
    for (auto it = unitList.begin(); it != unitList.end();) {
        Unit* unit = gameHandler->findUnit(*it);
        if (unit == nullptr || unit->isDead()) {
            it = unitList.erase(it);
        }
        else {
            it++;
        }
    }

    if (unitList.size() < unitCap) {
        Unit* unit = createUnit();
        if (unit != nullptr) {
            unitList.push_back(unit->getId());
            unit->setTeam(team);
            unit->setXY(x, y);
            unit->setTargetXY(targetX, targetY);
        }
    }
}

Unit* Citadel::createUnit () {
    switch (rand() % 6) {
        case 0:
            return gameHandler->createUnit("Swordsmen");
        case 1:
            return gameHandler->createUnit("Spearmen");
        case 2:
            return gameHandler->createUnit("Archers");
        case 3:
            return gameHandler->createUnit("Crossbowman");
        case 4:
            return gameHandler->createUnit("Rider");
        case 5:
            return gameHandler->createUnit("Knight");
        default:
            throw outOfBoundsException("Unknown citadel unit generation type");
    }
}

void Citadel::save (ostream& os) {
    Unit::save(os);
    int size = unitList.size();
    os << unitCap << ' ' << unitTypeIndex << ' ' << size << endl;
    for(int i = 0; i < size; i++) {
        int id = unitList[i];
        os << id << ' ';
    }
    os << endl;
}

void Citadel::load (istream& is) {
    Unit::load(is);
    int size;
    is >> unitCap >> unitTypeIndex >> size;
    for(int i = 0; i < size; i++) {
        int id;
        is >> id;
        unitList.push_back(id);
    }
}

const string& Citadel::getType () {
    return type;
}

