#include "base.h"

#include "qglobal.h"

Base::Base(Point2D* point, Mediator* mediator)
{
    this->coordinate = point;
    this->mediator = mediator;

    Armor* armor = new NoArmor;
    Weapon* weapon = new NoWeapon;

    this->health = 200;
    this->armor = armor;
    this->weapon = weapon;
    numberOfUnits = 0;
}


bool Base::isFlying()
{
    return false;
}


Unit* Base::createInfantryUnit(int dx, int dy)
{
    Unit* unit = nullptr;

    Point2D* coord = this->coordinate->clone();
    coord->x += dx;
    coord->y += dy;

    int i = generateRandomNum(2);

    UnitFactory* factory;

    switch (i) {
    case 0:
        factory = new SwordsmanFactory;
        unit = factory->createUnit(this->mediator);
        unit->setCoordinate(coord);
        delete factory;
        break;
    case 1:
        factory = new DwarfFactory;
        unit = factory->createUnit(this->mediator);
        unit->setCoordinate(coord);
        delete factory;
    }

    return createUnit(unit);
}


Unit* Base::createFlyingUnit(int dx, int dy)
{
    Unit* unit = nullptr;

    Point2D* coord = this->coordinate->clone();
    coord->x += dx;
    coord->y += dy;

    int i = generateRandomNum(2);

    UnitFactory* factory;

    switch (i) {
    case 0:
        factory = new DragonFactory;
        unit = factory->createUnit(mediator);
        unit->setCoordinate(coord);
        delete factory;
        break;
    case 1:
        factory = new HarpyFactory;
        unit = factory->createUnit(mediator);
        unit->setCoordinate(coord);
        delete factory;
    }

    return createUnit(unit);
}


Unit* Base::createStandingUnit(int dx, int dy)
{
    Unit* unit = nullptr;

    Point2D coord;
    coord = *(this->coordinate);
    coord.x += dx;
    coord.y += dy;

    int i = generateRandomNum(2);

    UnitFactory* factory;

    switch (i) {
    case 0:
        factory = new ArcherFactory;
        unit = factory->createUnit(mediator);
        unit->setCoordinate(&coord);
        delete factory;
        break;
    case 1:
        factory = new LiveShieldFactory;
        unit = factory->createUnit(mediator);
        unit->setCoordinate(&coord);
        delete factory;
    }

    return createUnit(unit);
}


void Base::update()
{
    this->numberOfUnits--;
}


size_t Base::getNumberOfUnits()
{
    return this->numberOfUnits;
}


void Base::regeneration()
{
    this->health += LOW_REGENERATION_ABILITY;
}


Unit* Base::clone()
{
    Unit* base(new Base(*this));
    return base;
}


char Base::draw()
{
    return 'B';
}


bool Base::move(int dx, int dy)
{
    Q_UNUSED(dx);
    Q_UNUSED(dy);

    return false;
}



int Base::generateRandomNum(int end) const
{
    srand(time(0));
    return rand() % (end) ;
}


Unit* Base::createUnit(Unit* unit)
{
    if (numberOfUnits < MAX_NUMBER_OF_UNITS
            && mediator->notify(unit, unit->getCoordiante().x, unit->getCoordiante().y)) {
        numberOfUnits++;
        return unit;
    }

    return nullptr;
}
