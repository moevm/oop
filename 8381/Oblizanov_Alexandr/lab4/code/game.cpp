#include "game.h"

Game::Game(unsigned x, unsigned y, unsigned limit, LandType basicLand)
{
    this->field = new Field(x, y, limit, basicLand);
    units = new AttackMediator(field);
}

void Game::createBase(std::string name, unsigned limit, unsigned x, unsigned y)
{
    Base *base = new Base(limit, static_cast<unsigned>(bases.size()), name, field);
    try {
        field->addItem(x, y, base);
        baseMediator = new GameMediator(this, base);
        base->setGameMediator(baseMediator);
    } catch (std::logic_error a) {
        delete base;
        throw a;
    }
    bases.push_back(base);
}

Field *Game::getField() const
{
    return field;
}

std::vector<Base *> Game::getBases() const
{
    return bases;
}

Base *Game::getBaseByNumber(unsigned number)
{
    for (auto i : bases)
    {
        if (i->getNumber() == number)
            return i;
    }
    return nullptr;
}

void Game::addUnit(IUnit *unit, Base *base)
{
    bool checkBase = false;
    for (auto i : bases)
        if (i == base)
            checkBase = true;
    if (!checkBase)
        throw std::invalid_argument("Error! Invalid base tries to add unit to game");
    units->addUnit(unit);
}

void Game::deleteUnit(IUnit *unit, Base *base)
{
    bool checkBase = false;
    for (auto i : bases)
        if (i == base)
            checkBase = true;
    if (!checkBase)
        throw std::invalid_argument("Error! Invalid base tries to add unit to game");
    units->removeUnit(unit);
}

void Game::createNeutral(unsigned x, unsigned y, NeutralType type)
{
    srand(static_cast<unsigned>(time(nullptr)));
    INeutral *neutral;
    switch (type) {
    case CHEST:
        neutral = new Chest(rand() % 40);
        break;
    case KEYGEN:
        neutral = new Keygen(rand() % 40, rand() % 20);
        break;
    case ANTIVIRUS:
        neutral = new Antivirus(rand() % 40, rand() % 20);
        break;
    case DATA:
        neutral = new Data(rand() % 40);
    }
    try {
        field->addItem(x, y, neutral);
    } catch (std::logic_error a) {
        delete neutral;
        throw a;
    }
}

std::vector<IUnit *> Game::getUnits() const
{
    return units->getUnits();
}
