#include "Tower.h"
#include "Mediator.h"
#include "UnitFactory.h"
#include "Unit.h"


Tower::Tower(int x, int y, std::shared_ptr<UnitFactory> factory){
	xCoord = x;
	yCoord = y;
	level = 0;
	hp = 500;
	damage = 200;
	size = 2;
	unitCount = 0;
	this->factory = factory;

    switch (factory->getType()) {
    case UnitType::BITING_ZOMBY:
        kind = Kind::ZOMBY;
        break;
    case UnitType::STINKY_ZOMBY:
        kind = Kind::ZOMBY;
        break;
    case UnitType::STRONG_ZOMBY:
        kind = Kind::ZOMBY;
        break;
    case UnitType::KAMIKADZE_ZOMBY:
        kind = Kind::ZOMBY;
        break;
    case UnitType::SPIT_TO_AREA_ZOMBY:
        kind = Kind::ZOMBY;
        break;
    case UnitType::SPIT_TO_ENEMY_ZOMBY:
        kind = Kind::ZOMBY;
        break;
    default:
        kind = Kind::HUMAN;
        break;
    }
}

Tower::Tower(int level, int hp, int damage, int size, int unitCount, Kind kind, std::shared_ptr<UnitFactory> factory, std::shared_ptr<Mediator> mediator, int xCoord, int yCoord)
: level(level), hp(hp), damage(damage), size(size), unitCount(unitCount), kind(kind), factory(factory), mediator(mediator) {
    this->xCoord = xCoord;
    this->yCoord = yCoord;
}

Tower::Tower(const Tower & other)
{
	xCoord = other.xCoord;
	yCoord = other.yCoord;
	level = other.level;
	hp = other.hp;
	damage = other.damage;
	size = other.size;
	unitCount = other.unitCount;
	factory = std::shared_ptr<UnitFactory>(new UnitFactory(*other.factory));
}

Tower::Tower(Tower && other)
{
	xCoord = other.xCoord;
	yCoord = other.yCoord;
	level = other.level;
	hp = other.hp;
	damage = other.damage;
	size = other.size;
	unitCount = other.unitCount;
	factory = std::shared_ptr<UnitFactory>(new UnitFactory(*other.factory));

	other.factory = nullptr;
}


Tower::~Tower()
{
}

void Tower::update() {
	unitCount--;
    /*for (size_t i = 0; i < unitArr.size(); i++) {
        if (unitArr[i]->isDead()) {
            unitArr.erase(unitArr.begin() + i);
        }
    }*/
}

void Tower::levelUp() {
	level++;
    size = 2 + level/5;
}

void Tower::updateKill() {
	levelUp();
}

bool Tower::canCreateUnit()
{
	return unitCount < size;
}

std::shared_ptr<Unit> Tower::createUnit(int x, int y, int level) {
	if (unitCount < size) {
		unitCount++;
		std::shared_ptr<Unit> unit = factory->create(x, y, level);
		unit->setMediator(mediator);
        unit->registerObserever(shared_from_this());
        //unitArr.push_back(unit);
		return unit;
	}
	std::cout << "\nНевозможно создать юнита, уровень башни слишком низок\n";
	return nullptr;
}

int Tower::getLevel()
{
	return level;
}

void Tower::damageTower(int damage) {
	hp -= damage;
}

int Tower::getHP()
{
	return hp;
}

int Tower::getDamage()
{
	return damage;
}

void Tower::setMediator(std::shared_ptr<Mediator> mediator) {
	this->mediator = mediator;
}

void Tower::attack() {
    mediator->reactOnTowerAttack(shared_from_this());
}

int Tower::getX()
{
	return xCoord;
}

int Tower::getY()
{
	return yCoord;
}

int Tower::getSize()
{
	return size;
}

std::shared_ptr<TowerSnapshot> Tower::getSnapshot()
{
    return std::shared_ptr<TowerSnapshot>(new TowerSnapshot(level, hp, damage, size, unitCount, kind, factory, xCoord, yCoord));
}

std::ostream& operator<<(std::ostream &out, std::shared_ptr<Tower> tower) {
	out << "Tower state: hp = " << tower->getHP() << " level = " << tower->getLevel() << "damage = " << tower->getDamage() << " size = " << tower->getSize() << std::endl;
	return out;
}


std::shared_ptr<UnitFactory> Tower::getFactory() {
    return factory;
}


int Tower::getUnitCount() {
    return unitCount;
}


/*std::shared_ptr<Unit> Tower::getUnit(int index) {
    return unitArr[index];
}*/


Kind Tower::getKind() {
    return kind;
}
