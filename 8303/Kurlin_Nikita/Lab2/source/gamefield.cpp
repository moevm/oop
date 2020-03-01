#include "gamefield.h"

GameField::GameField(int x, int y, int maxCount) : x(x), y(y), unitCount(0), maxCount(maxCount)
{		
    pointsMap = new Point** [y];

    for (int i = 0; i < y; i++) {
        pointsMap[i] = new Point*[x];
        for (int j = 0; j < x; j++){
            pointsMap[i][j] = new Point;
            pointsMap[i][j]->unit = nullptr;
            pointsMap[i][j]->base = nullptr;
            pointsMap[i][j]->nObject = nullptr;
            pointsMap[i][j]->y = i;
            pointsMap[i][j]->x = j;

            int k = (i+j) % 3;
            if (k == 0)
                pointsMap[i][j]->landscape = new River();
            if (k == 1)
                pointsMap[i][j]->landscape = new Mountain();
            if (k == 2)
                pointsMap[i][j]->landscape = new Forest();
            if (i == 0 && j == 0)
                pointsMap[i][j]->nObject = new DrinkPoison();
            if (i == 0 && j == x - 1)
                pointsMap[i][j]->nObject = new GetArmor();
            if (i == y - 1 && j == 0)
                pointsMap[i][j]->nObject = new GetWeapon();
            if (i == y - 1 && j == x - 1)
                pointsMap[i][j]->nObject = new GetMedicine();
        }
    }
}

//Конструктор копирования
GameField::GameField(const GameField &field) : x(field.x), y(field.y), unitCount(field.unitCount), maxCount(field.maxCount), pointsMap(new Point** [field.y])
{
    for (int i = 0; i < y; i++) {
        pointsMap[i] = new Point*[x];
        for (int j = 0; j < x; j++)
            pointsMap[i][j] = field.pointsMap[i][j];
    }
}

//Конструктор перемещения
GameField::GameField(GameField &&field) : x(field.x), y(field.y), unitCount(field.unitCount), maxCount(field.maxCount), pointsMap(new Point**[field.y])
{
    for (int i = 0; i < y; i++) {
        pointsMap[i] = new Point*[x];
        for (int j = 0; j < x; j++)
            pointsMap[i][j] = field.pointsMap[i][j];
    }
    for(int i = 0; i < y; i++)
        delete[] field.pointsMap[i];
    delete[] field.pointsMap;
}

bool GameField::addUnit(Unit* unit, int xx, int yy)
{
    if ((xx <= this->x - 1) && (yy <= this->y - 1) && (xx >= 0) && (yy >= 0) && (!pointsMap[yy][xx]->unit) && pointsMap[yy][xx]->landscape->canStand(unit)) {
        if (unitCount < maxCount) {
            pointsMap[yy][xx]->unit = unit;
            unitCount++;
            return true;
        }
    }
    return false;
}

void GameField::deleteUnit(Unit* unit)
{
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (unit == pointsMap[i][j]->unit) {
                pointsMap[i][j]->unit = nullptr;
                unitCount--;
                return;
            }
        }
    }
}

Point* GameField::findUnit(Unit *unit)
{
    for (int i = 0; i < this->y; i++){
        for (int j = 0; j < this->x; j++){
            if (pointsMap[i][j]->unit == unit){
                return pointsMap[i][j];
            }
        }
    }
    return nullptr;
}

void GameField::moveUnit(Unit* unit, int xx, int yy)
{
    if ((xx <= this->x - 1) && (yy <= this->y - 1) && (xx >= 0) && (yy >= 0) && (!pointsMap[yy][xx]->unit) &&
            (!pointsMap[yy][xx]->base) && pointsMap[yy][xx]->landscape->canStand(unit)) {
        deleteUnit(unit);
        addUnit(unit, xx, yy);
    }
}

void GameField::moveUnitLeft(Unit *unit)
{
    Point* p = this->findUnit(unit);
    moveUnit(unit, p->x - 1, p->y);
}

void GameField::moveUnitRight(Unit *unit)
{
    Point* p = this->findUnit(unit);
    moveUnit(unit, p->x + 1, p->y);
}

void GameField::moveUnitUp(Unit *unit)
{
    Point* p = this->findUnit(unit);
    moveUnit(unit, p->x, p->y - 1);
}

void GameField::moveUnitDown(Unit *unit)
{
    Point* p = this->findUnit(unit);
    moveUnit(unit, p->x, p->y + 1);
}

void GameField::printAll() const
{
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (pointsMap[i][j]->base != nullptr){
                std::cout << "B";
                continue;
            }
            if (pointsMap[i][j]->unit != nullptr) {

                std::cout << 1;
            }
            else
                std::cout << 0;
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (pointsMap[i][j]->landscape->getLandscapeType() == "Forest") {
                std::cout << "*";
            }
            else if (pointsMap[i][j]->landscape->getLandscapeType() == "Mountain")
                std::cout << "^";
            else
                std::cout << "~";
        }
        std::cout << std::endl;
    }
}

Base* GameField::setBase(int xx, int yy, int maxCount, int health)
{
    if ((xx <= this->x - 1) && (yy <= this->y - 1) && (xx >= 0) && (yy >= 0)) {
        Base* base = new Base(maxCount, health, xx, yy, this);
        pointsMap[yy][xx]->base = base;
        return base;
    }
}
