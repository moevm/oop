#include "game.hpp"

void
GameCell::destroy()
{
    delete _unit;
    _unit = nullptr;
}

void
GameCell::copy_from(const GameCell &c)
{
    _unit = c._unit ? c._unit->copy() : nullptr;
}

void
GameCell::move_from(GameCell &&c)
{
    _unit = c._unit;
    c._unit = nullptr;
}
