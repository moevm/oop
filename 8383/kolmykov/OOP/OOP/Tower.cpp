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
}

Tower::Tower(int level, int hp, int damage, int size, int unitCount, std::shared_ptr<UnitFactory> factory, std::shared_ptr<Mediator> mediator)
: level(level), hp(hp), damage(damage), size(size), unitCount(unitCount), factory(factory), mediator(mediator){
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
}

void Tower::levelUp() {
	level++;
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
	mediator->reactOnTowerAttack(std::shared_ptr<Tower> (this));
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
	return std::shared_ptr<TowerSnapshot>(new TowerSnapshot(level, hp, damage, size, unitCount, factory));
}

std::ostream& operator<<(std::ostream &out, std::shared_ptr<Tower> tower) {
	out << "Tower state: hp = " << tower->getHP() << " level = " << tower->getLevel() << "damage = " << tower->getDamage() << " size = " << tower->getSize() << std::endl;
	return out;
}