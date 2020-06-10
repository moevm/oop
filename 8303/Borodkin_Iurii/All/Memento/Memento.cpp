#include "Memento.h"

Memento::Memento(GameField* s) : state(s)
{}

GameField* Memento::getState() const
{
    return state;
}

GameField* &Memento::getState()
{
    return state;
}
