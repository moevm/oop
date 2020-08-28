#include "unit.hpp"
#include "../tiles/tile.hpp"
#include "../tiles/fortress.hpp"
#include "../exceptions/out_of_bounds_exception.hpp"
#include "../exceptions/saving_exception.hpp"
#include "../exceptions/loading_exception.hpp"

static const char sprite[3][3] = {{' ', ' ', ' '},
                                  {' ', '@', ' '},
                                  {' ', ' ', ' '}};

Unit::Unit () {
    hp = Unit::getMaxHP();
}

Unit::~Unit () {

}

bool Unit::isDead () const {
    return hp <= 0;
}

void Unit::validateChar (int x, int y) {
    if (x < 0 || y < 0 || x > 2 || y > 2) throw outOfBoundsException("Unit sprite output error");
}

char Unit::getChar (int x, int y) {
    validateChar(x, y);
    return sprite[y][x];
}

MovingType Unit::getMovingType () {
    return IMMOBILE;
}

void Unit::setTeam (Team team) {
    this->team = team;
}

Team Unit::getTeam () {
    return team;
}

int Unit::getId () const {
    return id;
}

int Unit::getX () const {
    return x;
}

int Unit::getY () const {
    return y;
}

void Unit::setXY (int x, int y) {
    this->x = x;
    this->y = y;
}

int Unit::sqrDistanceTo (int x, int y) const {
    int dx = this->x - x;
    int dy = this->y - y;
    return dx * dx + dy * dy;
}

int Unit::getTargetX () const {
    return targetX;
}

int Unit::getTargetY () const {
    return targetY;
}

void Unit::setTargetXY (int x, int y) {
    int sx = gameHandler->getSizeX();
    int sy = gameHandler->getSizeY();
    targetX = (x + sx) % sx;
    targetY = (y + sy) % sy;
}

void Unit::onGameFieldEnter (const int id, Unit::GameHandler* game) {
    this->id = id;
    this->gameHandler = game;
}

void Unit::update () {
    Unit* targetUnit = gameHandler->findUnit(targetUnitId);
    if (targetUnit != nullptr) {
        if (targetUnit->isDead() || pow(visionDistance(), 2) < targetUnit->sqrDistanceTo(x, y) || !isAttackable(targetUnit)) {
            targetUnitId = -1;
            targetUnit = nullptr;
        }
    }
    else {
        targetUnitId = -1;
    }

    if (targetUnit == nullptr && getDamageType() != NONE) {
        auto unitList = gameHandler->findUnits(x, y, visionDistance());
        for (auto other : *unitList) {
            other->spotted(this);
            if (other->getTeam() != team) {
                if (targetUnit == nullptr || targetUnit->sqrDistanceTo(x, y) < other->sqrDistanceTo(x, y)) {
                    if (isAttackable(other)) {
                        targetUnit = other;
                        targetUnitId = other->getId();
                    }
                }
            }
        }
    }

    if (targetUnit == nullptr) {
        walkTo(targetX, targetY);
    }
    else if (targetUnit->sqrDistanceTo(x, y) > attackDistance()) {
        walkTo(targetUnit->getX(), targetUnit->getY());
    }
    else {
        dealDamage(targetUnit);
    }
}

void Unit::spotted (Unit* other) {

}

int Unit::getMaxHP () {
    return 1;
}

int Unit::attackDistance () {
    return 1;
}

int Unit::visionDistance () {
    return 2;
}

int Unit::getSpeed () {
    return 1;
}

DamageType Unit::getDamageType () {
    return NONE;
}

int Unit::getDamage () {
    return 0;
}

void Unit::takeDamage (DamageType damageType, int value) {
    if (getMovingType() == HORSE && damageType == PRICKING) {
        value *= 2;
    }
    hp -= min(value, hp);
}

bool Unit::isAttackable (Unit* other) {
    if (getDamageType() == ARROW) {
        Tile* thisTile = gameHandler->getTile(x, y);
        Tile* targetTile = gameHandler->getTile(other->getX(), other->getY());
        return thisTile == targetTile || targetTile->getId() != Fortress::id;
    }
    return true;
}

void Unit::dealDamage (Unit* other) {
    gameHandler->getLogger().log(getType() + " " + to_string(getId()) + " --> " + other->getType() + " " + to_string(other->getId()));
    other->takeDamage(getDamageType(), getDamage());
}

bool Unit::moveTo (int x, int y) {
    if (getMovingType() != IMMOBILE && gameHandler->onField(x, y)) {
        Tile* thisTile = gameHandler->getTile(this->x, this->y);
        Tile* targetTile = gameHandler->getTile(x, y);

        if (thisTile == targetTile || targetTile->allow(getMovingType())) {
            this->x = x;
            this->y = y;
            return true;
        }
    }
    return false;
}

bool Unit::stepTo (int x, int y) {
    int dx = x - this->x;
    int dy = y - this->y;
    if (abs(dx) > abs(dy)) {
        return moveTo(this->x + (dx > 0 ? 1 : -1), this->y);
    }
    else {
        return moveTo(this->x, this->y + (dy > 0 ? 1 : -1));
    }
}

bool Unit::walkTo (int x, int y) {
    for (int i = 0; i < getSpeed(); i++) {
        if (!stepTo(x, y)) {
            return false;
        }
        else if (this->x == x && this->y == y) {
            return true;
        }
    }
    return true;
}

void Unit::save (ostream& os) {
    os << team << ' ';
    os << x << ' ' << y << ' ';
    os << targetX << ' ' << targetY << ' ';
    os << targetUnitId << ' ';
    os << hp << endl;
}

void Unit::load (istream& is) {
    int t;
    if (!(is >> t)) throw loadingException("team incorrect");
    team = static_cast<Team>(t);
    if (!(is >> x >> y)) throw loadingException("x or y incorrect");
    if (!(is >> targetX >> targetY)) throw loadingException("targetx or targety incorrect");
    if (!(is >> targetUnitId)) throw loadingException("targetUnitId incorrect");
    if (!(is >> hp)) throw loadingException("hp incorrect");
}

void Unit::operator*(Unit *other) {
    dealDamage(other);
}

void Unit::operator<(Unit *other) {
    spotted(other);
}





