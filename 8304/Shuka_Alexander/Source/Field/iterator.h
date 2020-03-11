#ifndef ITERATOR_H
#define ITERATOR_H

#include "Field/gamefield.h"


class GameField;


class GameFieldIterator
{
public:
    GameFieldIterator(const GameField& gameField);

    bool hasNext() const;
    void first();
    friend const GameFieldIterator& operator++(GameFieldIterator& it);
    friend const GameFieldIterator operator++(GameFieldIterator& it, int);
    CellOfField& operator*() const;

private:
    size_t i;
    size_t j;
    size_t width;
    size_t height;
    const GameField& gameField;
};

#endif // GameFieldIterator_H
