#include "base.hpp"

Base::Base(const Position2D& position, std::shared_ptr<Mediator> mediator,PLAYER player) : Unit(position, mediator)
{
    HeavyArmorFactory armorFactory;
    BallisticWeaponFactory weaponFactory;

    healthPoints = 300;
    this->player = player;
    unitName = "Base";
    armor = armorFactory.createArmor();
    weapon = weaponFactory.createWeapon();
    numberOfUnits = 0;
}


bool Base::moveLeft()
{
    return false;
}


bool Base::moveTop()
{
    return false;
}


bool Base::moveBottom()
{
    return false;
}


bool Base::moveRight()
{
    return false;
}

std::shared_ptr<Unit> Base::createShortRangeUnit(int dx, int dy)
{
    int num = generateRandomNum(2);
    std::shared_ptr<Unit> unit;
    Position2D pos = this->position;
    pos.x += dx;
    pos.y += dy;

    switch (num) {
    case 0:
        unit = creator.createSwordMan(pos, mediator);
        break;
    case 1:
        unit = creator.createSpearMan(pos, mediator);
        break;
    }

    return createUnit(unit);
}


std::shared_ptr<Unit> Base::createLongRangeUnit(int dx, int dy)
{
    int num = generateRandomNum(2);
    std::shared_ptr<Unit> unit;
    Position2D pos = this->position;
    pos.x += dx;
    pos.y += dy;

    switch (num) {
    case 0:
        unit = creator.createArcher(pos, mediator);
        break;
    case 1:
        unit = creator.createBallistic(pos, mediator);
        break;
    }

    return createUnit(unit);
}


std::shared_ptr<Unit> Base::createDynamicRangeUnit(int dx, int dy)
{
    int num = generateRandomNum(2);
    std::shared_ptr<Unit> unit;
    Position2D pos = this->position;
    pos.x += dx;
    pos.y += dy;

    switch (num) {
    case 0:
        unit = creator.createVampire(pos, mediator);
        break;
    case 1:
        unit = creator.createDragon(pos, mediator);
        break;
    }

    return createUnit(unit);
}


std::shared_ptr<Unit> Base::clone()
{
    std::shared_ptr<Unit> base(new Base(*this));
    return base;
}


//char Base::draw() const
//{
//    return 'B';
//}


void Base::update()
{
    --numberOfUnits;
}

void Base::baseInfo(){
    std::cout<<"Base info: \n";
    std::cout<<"Health points: " << healthPoints <<"\n";
    std::cout<<"Base resistance: " << armor->getResistance()<<"\n";
    std::cout<<"Number of Unit: " << numberOfUnits <<" out of " << MAX_NUMBER_UNITS <<"\n";

}

int Base::generateRandomNum(int end) const
{
    srand(time(0));
    return rand() % end;
}


std::shared_ptr<Unit> Base::createUnit(std::shared_ptr<Unit> unit)
{
    if (numberOfUnits < MAX_NUMBER_UNITS &&  mediator->notify(unit, CREATE_UNIT)) {
        unit->addObserver(shared_from_this());
        unit->setPlayer(this->player);
        numberOfUnits++;
        return unit;
    }

    return nullptr;
}
