#include "gamefield.h"

GameField::GameField(size_t height, size_t width) :
    height(height), width(width),
    array(std::make_unique<std::unique_ptr<CellOfField[]>[]>(height))

{
    this->nUnits = 0;

    for (size_t i = 0; i < height; ++i) {
        array[i] = std::make_unique<CellOfField[]>(width);
    }
}


GameField::GameField(const GameField& gameField)
{
    array = std::make_unique<std::unique_ptr<CellOfField[]>[]>(gameField.height);

    height = gameField.height;
    width = gameField.width;
    nUnits = gameField.nUnits;

    for (size_t i = 0; i < height; ++i) {
        array[i] = std::make_unique<CellOfField[]>(width);
    }

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            array[i][j] = gameField.array[i][j];
        }
    }
}


GameField& GameField::operator=(const GameField& gameField)
{
    if (this == &gameField) {
        return *this;
    }

    for (size_t i = 0; i < height; ++i) {
        array[i].reset();
    }
    array.reset();

    array = std::make_unique<std::unique_ptr<CellOfField[]>[]>(gameField.height);

    height = gameField.height;
    width = gameField.width;
    nUnits = gameField.nUnits;

    for (size_t i = 0; i < height; ++i) {
        array[i] = std::make_unique<CellOfField[]>(width);
    }

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            array[i][j] = gameField.array[i][j];
        }
    }

    return *this;
}


GameField::GameField(GameField&& gameField)
{
    height = gameField.height;
    width = gameField.width;
    nUnits = gameField.nUnits;

    gameField.height = 0;
    gameField.width = 0;
    gameField.nUnits = 0;

    array = std::move(gameField.array);
}


GameField& GameField::operator=(GameField&& gameField)
{
    if (this == &gameField) {
        return* this;
    }

    for (size_t i = 0; i < height; ++i) {
        array[i].reset();
    }
    array.reset();

    height = gameField.height;
    width = gameField.width;
    nUnits = gameField.nUnits;

    gameField.height = 0;
    gameField.width = 0;
    gameField.nUnits = 0;

    array = std::move(gameField.array);

    return *this;
}


size_t GameField::getWidth() const
{
    return width;
}


size_t GameField::getHeight() const
{
    return height;
}


size_t GameField::getNUnits() const
{
    return nUnits;
}


bool GameField::addUnit(std::shared_ptr<Unit> unit)
{
    Point2D point = unit->getPosition();

    if (!array[point.y][point.x].isEmpty()) {
        return false;
    }

    array[point.y][point.x].addUnit(unit);

    return true;
}


bool GameField::isEmpty(const Point2D& point) const
{
    return array[point.y][point.x].isEmpty();
}


void GameField::moveUnit(std::shared_ptr<Unit> unit, const Point2D& point)
{
    array[point.y][point.x].addUnit(unit);
    array[unit->getPosition().y][unit->getPosition().x].deleteUnit();
}


void GameField::deleteUnit(std::shared_ptr<Unit> unit)
{
    auto it = this->getIterator();

    for (it->first(); it->hasNext(); ++*it) {
        if ((**it).getUnit() == unit) {
            (**it).deleteUnit();
        }
    }
    unit.reset();
}


std::unique_ptr<GameFieldIterator> GameField::getIterator() const
{
    return std::unique_ptr<GameFieldIterator>(new GameFieldIterator(*this));
}
