#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <memory>

#include "Field/celloffield.h"
#include "Field/point2d.h"
#include "Field/iterator.h"


class GameFieldIterator;


class GameField
{
    friend class GameFieldIterator;

public:
    explicit GameField(size_t height, size_t width);
    virtual ~GameField() = default;

    GameField(const GameField& gameField);
    GameField& operator=(const GameField& gameField);
    GameField(GameField&& gameField);
    GameField& operator=(GameField&& gameField);

    size_t getWidth() const;

    size_t getHeight() const;

    size_t getNUnits() const;

    bool addUnit(std::shared_ptr<Unit> unit);

    std::shared_ptr<Unit>& getUnit(const Point2D& point) const;

    bool isEmpty(const Point2D& point) const;

    void moveUnit(std::shared_ptr<Unit> unit, const Point2D& point);

    void deleteUnit(std::shared_ptr<Unit> unit);

    std::unique_ptr<GameFieldIterator> getIterator() const;

private:
    size_t nUnits;
    size_t height;
    size_t width;
    std::unique_ptr<std::unique_ptr<CellOfField[]>[]> array;
};

#endif // GAMEFIELD_H
