#include "GameField.h"
#include "../Exceptions/StackExceptions.h"


GameField::GameField():
        fieldHeight(0),
        fieldWidth(0),
        field(nullptr)
{}

void GameField::setBorders(){
    int i;
    int j;
    for(i = 0, j = 0; i < fieldHeight; i++) {
        Border *border;
        field[i][j].setTerrain(border);
        field[i][j].changeMovable(false);
    }
    for(i = 0, j = 0; j < fieldWidth; j++) {
        Border *border;
        field[i][j].setTerrain(border);
        field[i][j].changeMovable(false);
    }

    for(i = 0, j = fieldWidth - 1; j >= 0; j--) {
        Border *border;
        field[i][j].setTerrain(border);
        field[i][j].changeMovable(false);
    }
    for(i = fieldHeight - 1, j = 0; j < fieldWidth; j++) {
        Border *border;
        field[i][j].setTerrain(border);
        field[i][j].changeMovable(false);
    }
}

GameField::GameField(int fieldHeight, int fieldWidth):
        fieldHeight(fieldHeight),
        fieldWidth(fieldWidth)
{
    field = new FieldCell* [fieldHeight];
    for (int i = 0; i < fieldHeight; i++){
        field[i] = new FieldCell [fieldWidth];
    }
}

void GameField::deleteObject(int x, int y) {

    if (y < 0 || y > fieldHeight || x < 0 || x > fieldWidth){
        throw OutOfRangeExc(x, y);
    }
    field[y][x].eraseObject();

}

bool GameField::addObject(GameObject *object, int x, int y) {

    if (object->isOnField){
        Log::log << "[#GameField] Impossible addition of " << *object << " on field" << Log::logend;
        throw DoublePlacingExc();
    }

    bool isInBorder = x < fieldWidth && y < fieldHeight && x >= 0 && y >= 0;

    if (isInBorder && field[y][x].isEmpty()){

        field[y][x].setObject(object);
        object->pos = Point(x, y);
        object->isOnField = true;

    } else{

        Log::log << "[#GameField] Impossible addition of " << *object << " on field" << Log::logend;
        throw OutOfRangeExc(x, y);

    }

    return true;
}

void GameField::deleteObject(GameObject *object) {
    deleteObject(object->pos.x, object->pos.y);
}

void GameField::moveObject(const Point &p1, const Point &p2) {

    if (checkBorder(p1) && checkBorder(p2) && !field[p1.y][p1.x].isEmpty() && field[p2.y][p2.x].isEmpty()){

        field[p2.y][p2.x] = std::move(field[p1.y][p1.x]);
        field[p2.y][p2.x].getObject()->pos = p2;
        field[p1.y][p1.x].eraseObject();

    } else{

        Log::log << "[#GameField] Impossible to move object from " << p1.x << " " << p1.y << " to " << p2.x << " " << p2.y << Log::logend;
        throw ImpossibleMoveExc();

    }

}


void GameField::deleteObject(const Point &point) {
    deleteObject(point.x, point.y);
}


FieldCell *GameField::getCell(const Point &p) const{

    if (p.x < fieldWidth && p.y < fieldHeight)
        return &field[p.y][p.x];
    throw OutOfRangeExc(p.x, p.y);
}

FieldCell *GameField::getCell(const int x, const int y) {
    if (x < fieldWidth && y < fieldHeight)
        return &field[y][x];
    throw OutOfRangeExc(x, y);
}

GameField::~GameField() {

    for (int i=0; i<fieldHeight; i++){
        delete []field[i];
    }

    delete []field;

}

void GameField::reset() {

    for (int i=0; i<fieldHeight; i++){
        delete []field[i];
    }

    delete []field;

    field = new FieldCell* [fieldHeight];
    for (int i=0; i<fieldHeight; i++){
        field[i] = new FieldCell [fieldWidth];
    }
}

std::ostream &operator<<(std::ostream &stream, const GameField &field) {

    for (int y = 0; y < field.fieldHeight; y++){
        for (int x = 0; x < field.fieldWidth; x++){
            stream << field.field[y][x];
        }
        stream << std::endl;
    }
    return stream;
}

void GameField::onUnitMove(Unit *unit, Point p) {

    FieldCell *cell = getCell(p);

    if (!cell->isEmpty() && cell->getObject()->getType() == ObjectType::NEUTRAL_OBJECT){

        auto *neutralObject = dynamic_cast<NeutralObject*>(cell->getObject());

        switch (unit->getUnitType()){
            case UnitType::INFANTRY:
                neutralObject->setStrategy(new InfantryStrategy());
                break;
            case UnitType::ARCHER:
                neutralObject->setStrategy(new ArcherStrategy());
                break;
            case UnitType::DRUID:
                neutralObject->setStrategy(new DruidStrategy());
                break;
        }
        (*unit) << neutralObject;
        cell->eraseObject();
    }
    moveObject(unit->getPosition(), p);

}

void GameField::onUnitDestroy(Unit *unit) {
    deleteObject(unit->getPosition());
}

bool GameField::addObject(GameObject *object, Point position) {
    return addObject(object, position.x, position.y);
}

void GameField::onBaseNewUnit(Unit *unit, Point pos) {

    bool isPossibleAdd = addObject(unit, pos);
    if (isPossibleAdd)
        unit->addObserver(this);

}

bool GameField::addBase(Base *base, Point pos) {

    return addBase(base, pos.x, pos.y);

}

bool GameField::addBase(Base *base, int x, int y) {

    bool isPossibleAdd = addObject(base, x, y);
    if (isPossibleAdd)
        base->addObserver(this);
    return isPossibleAdd;

}

void GameField::onUnitAttack(Unit *unit, Unit *enemy) {

    Terrain *terrain = getCell(unit->getPosition())->getTerrain();
    TerrainProxy terrainProxy(terrain);

    int damage = unit->getWeapon().getDamage() + terrainProxy.getDamageMultiply(unit->getWeapon().getType());
    int def = enemy->getArmor().controlAbsorb() + terrainProxy.getAbsorbMultiply(enemy->getArmor().getArmorType());

    int resDamage = damage - def;

    if (resDamage < 0)
        resDamage = 0;

    enemy->damage(resDamage);
}

bool GameField::checkBorder(const Point &p) const {
    return p.x >= 0 && p.y >= 0 && p.x < fieldWidth && p.y < fieldHeight;
}

