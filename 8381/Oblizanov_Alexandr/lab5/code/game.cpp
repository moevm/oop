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

GameMemento *Game::createMemento(std::string name)
{
    GameParameters param(field->getWidth(), field->getHeight(), field->getItemLimit(), field->getItemCounter(), bases.size());
    //making landscape info [getting from Field]
    for (unsigned i=0; i<field->getWidth(); i++)
    {
        for (unsigned j=0; j<field->getHeight(); j++)
        {
            param.landscape.push_back(field->getLandType(i, j));
        }
    }
    for (auto i : bases)
    {
        std::pair<unsigned, unsigned> coords = field->getItemCoords(i);
        BaseParameters bParam;
        //making base info [getting from bases vector in Game]
        bParam.x = coords.first;
        bParam.y = coords.second;
        bParam.number = i->getNumber();
        bParam.limit = i->getUnitLimit();
        bParam.stability = i->getStability();
        for (auto j : units->getUnits())
        {
            if (j->getBaseNumber() == i->getNumber())
            {
                //making unit info [getting from units vector in Game]
                UnitParameters uParam;
                coords = field->getItemCoords(j);
                uParam.x = coords.first;
                uParam.y = coords.second;
                uParam.type = static_cast<UnitType>(j->getType());
                uParam.move = j->getCharacteristics().getMove();
                uParam.power = j->getCharacteristics().getPower();
                uParam.spread = j->getCharacteristics().getSpread();
                uParam.charactBonus = j->getCharacteristics().getBonus();
                uParam.attackBonus = j->getAttackSkills().getBonus();
                uParam.securityBonus = j->getSecuritySkills().getBonus();
                bParam.units.push_back(uParam);
            }
        }
        param.bases.push_back(bParam);
    }
    //making neutrals info [getting from Field]
    int type;
    for (unsigned i=0; i<field->getWidth(); i++)
    {
        for (unsigned j=0; j<field->getHeight(); j++)
        {
            if (field->getItem(i, j) != nullptr)
            {
                type = field->getItem(i, j)->getType();
                if (type >= CHEST && type <= DATA)
                {
                    NeutralParameters nParam(static_cast<NeutralType>(type), i, j);
                    param.neutrals.push_back(nParam);
                }
            }
        }
    }
    return new GameMemento(name, param);
}

void Game::restoreMemento(IMemento *memento)
{
    GameParameters param = memento->loadFromFile();
    delete field;
    for (auto i : bases)
        delete i;
    bases.clear();
    delete units;
    field = new Field(param.width, param.height, param.itemLimit, OPEN);
    units = new AttackMediator(field);
    unsigned index = 0;
    //recreating landscape
    for (unsigned i=0; i<field->getWidth(); i++)
    {
        for (unsigned j=0; j<field->getHeight(); j++)
        {
            field->addLandscape(i, j, new ProxyLandscape(static_cast<LandType>(param.landscape[index++])));
        }
    }
    //recreating neutrals
    for (auto i : param.neutrals)
    {
        createNeutral(i.x, i.y, i.type);
    }
    //recreating bases and units
    for (auto i : param.bases)
    {
        createBase(std::to_string(i.number), i.limit, i.x, i.y);
        Base *base = getBaseByNumber(i.number);
        for (auto j : i.units)
        {
            Skills skills;
            skills.setAll(j.move, j.power, j.spread, j.charactBonus);
            IUnit *unit = base->createUnit(j.x, j.y, j.type);
            unit->setCharacteristics(skills);
            unit->setAttackBonus(j.attackBonus);
            unit->setSecurityBonus(j.securityBonus);
        }
    }
}

Game::~Game()
{
    delete field;
    delete units;
    for (auto i : bases)
        delete i;
}

std::vector<IUnit *> Game::getUnits() const
{
    return units->getUnits();
}
