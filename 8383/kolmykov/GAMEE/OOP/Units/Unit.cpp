#include "Unit.h"



Unit::Unit(int x, int y, int lvl) {
	coordX = x;
	coordY = y;
	level = lvl;
	observerCount = 0;
    observerSize = 0;
	landDamage = 0;
	landDefence = 0;
	visability = true;
    ownDamage = 5 * lvl;
    ownArmor = 2 * lvl;
	maxHP = 0;
	hp = 0;
    lastStep = 0;
}

Unit::Unit(const Unit & other) {
	this->hp = other.hp;
	this->maxHP = other.maxHP;
	this->ownArmor = other.ownArmor;
	this->ownDamage = other.ownDamage;
	this->coordX = other.coordX;
	this->coordY = other.coordY;
	this->visability = other.visability;
	this->level = other.level;
	this->landDamage = other.landDamage;
	this->landDefence = other.landDefence;

	this->armor = std::shared_ptr<Armor>(new Armor(*other.armor));
	this->weapon = std::shared_ptr<Weapon>(new Weapon(*other.weapon));

	this->moveBehavior = other.moveBehavior;
	this->attackBehavior = other.attackBehavior;
	this->kind = other.kind;
}

Unit::Unit(Unit && other) {
	this->hp = other.hp;
	this->maxHP = other.maxHP;
	this->ownArmor = other.ownArmor;
	this->ownDamage = other.ownDamage;
	this->coordX = other.coordX;
	this->coordY = other.coordY;
	this->visability = other.visability;
	this->level = other.level;
	this->landDamage = other.landDamage;
	this->landDefence = other.landDefence;

	this->armor = std::shared_ptr<Armor>(new Armor(*other.armor));
	other.armor = nullptr;
	this->weapon = std::shared_ptr<Weapon>(new Weapon(*other.weapon));
	other.weapon = nullptr;

	this->moveBehavior = other.moveBehavior;
	this->attackBehavior = other.attackBehavior;
	this->kind = other.kind;
}

Unit& Unit::operator=(const Unit& other)
{
	this->hp = other.hp;
	this->maxHP = other.maxHP;
	this->ownArmor = other.ownArmor;
	this->ownDamage = other.ownDamage;
	this->visability = other.visability;
	this->level = other.level;
	this->landDamage = other.landDamage;
	this->landDefence = other.landDefence;

	this->weapon = std::shared_ptr<Weapon>(new Weapon(*other.weapon));
	this->armor = std::shared_ptr<Armor>(new Armor(*other.armor));
	this->moveBehavior = std::shared_ptr<MoveBehavior>(new MoveBehavior(*other.moveBehavior));
	this->attackBehavior = std::shared_ptr<AttackBehavior>(new AttackBehavior(*other.attackBehavior));

	this->observerSize = 0;
	this->observerCount = 0;
	this->coordX = other.coordX;
	this->coordY = other.coordY;
	this->kind = other.kind;

	return *this;
}

Unit& Unit::operator=(Unit && other)
{
	if (&other == this) {
		return *this;
	}

	this->hp = other.hp;
	this->maxHP = other.maxHP;
	this->ownArmor = other.ownArmor;
	this->ownDamage = other.ownDamage;
	this->visability = other.visability;
	this->level = other.level;
	this->landDamage = other.landDamage;
	this->landDefence = other.landDefence;

	this->weapon = std::shared_ptr<Weapon>(new Weapon(*other.weapon));
	this->armor = std::shared_ptr<Armor>(new Armor(*other.armor));
	this->moveBehavior = std::shared_ptr<MoveBehavior>(new MoveBehavior(*other.moveBehavior));
	this->attackBehavior = std::shared_ptr<AttackBehavior>(new AttackBehavior(*other.attackBehavior));

	this->observerSize = 0;
	this->observerCount = 0;
	this->coordX = other.coordX;
	this->coordY = other.coordY;
	this->kind = other.kind;

	return *this;
}

Unit::Unit(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep) {
	this->hp = hp;
	this->maxHP = maxHP;
	this->ownArmor = ownArmor;
	this->ownDamage = ownDamage;
	this->visability = visability;
	this->level = level;
	this->landDamage = landDamage;
	this->landDefence = landDefence;
	this->observers = observers;
	this->observerSize = observerSize;
	this->observerCount = observerCount;
	this->coordX = coordX;
	this->coordY = coordY;
	this->mediator = mediator;
    this->lastStep = lastStep;
    //TODO laststep
}

Unit::Unit() {
	coordX = -1;
	coordY = -1;
	level = 0;
	observerCount = 0;
	landDamage = 0;
	landDefence = 0;
	visability = true;
	ownDamage = 0;
	ownArmor = 0;
    observerSize = 0;
    lastStep = 0;
}

Unit::~Unit(){

}





void Unit::performAttack() {
	attackBehavior->attack(shared_from_this());
}


void Unit::performMove() {
	moveBehavior->move(shared_from_this());
}


void Unit::damageUnit(int damage) {
    if (damage - armor->getDefend() - ownArmor - landDefence > 0) {
        hp -= damage - armor->getDefend() - ownArmor - landDefence;
	}
}

int Unit::getX()
{
	return coordX;
}

int Unit::getY()
{
	return coordY;
}

void Unit::setX(int x)
{
	coordX = x;
}

void Unit::setY(int y)
{
	coordY = y;
}

char Unit::getChar()
{
	return 'U';
}


void Unit::levelUp() {
	level++;
}

void Unit::registerObserever(std::shared_ptr<ObserverInterface> observer) {
	if (observerSize == 0) {
		observers = std::shared_ptr<std::shared_ptr<ObserverInterface>[]>(new std::shared_ptr<ObserverInterface>[1]);
        observers[0] = observer;
		observerSize = 1;
		observerCount = 1;
	}
	else if (observerCount < observerSize){
		for (int i = 0; i < observerSize; i++) {
			if (observers[i] == nullptr) {
				observers[i] = observer;
				observerCount++;
				break;
			}
		}
	}
	else {
		std::shared_ptr<std::shared_ptr<ObserverInterface>[]> ptr(new std::shared_ptr<ObserverInterface>[++observerSize]);
		for (int i = 0; i < observerSize - 1; i++) {
			ptr[i] = observers[i];
		}
		ptr[observerSize - 1] = observer;
		observers = ptr;
		observerCount++;
	}
}

void Unit::removeObserver(std::shared_ptr<ObserverInterface> observer) {
	for (int i = 0; i < observerSize; i++) {
		if (observers[i] == observer) {
			observers[i] == nullptr;
			observerCount--;
		}
	}
}

void Unit::notifyObservers() {
	for (int i = 0; i < observerSize; i++) {
		if (observers[i] != nullptr) {
			observers[i]->update();
		}
	}
}

void Unit::notifyAboutKill() {
	for (int i = 0; i < observerSize; i++) {
		if (observers[i] != nullptr) {
			observers[i]->updateKill();
		}
	}
}

void Unit::setVisability(bool visability)
{
	this->visability = visability;
}

bool Unit::getVisability()
{
	return visability;
}

void Unit::setLandDamage(int damage) {
	landDamage = damage;
}

void Unit::setLandDefence(int defence) {
	landDefence = defence;
}

void Unit::addHP(int hp) {
	this->hp += hp;
	if (hp > maxHP) {
		hp = maxHP;
	}
}

void Unit::addArmor(int defence)
{
	this->ownArmor += defence;
}

Kind Unit::getKind()
{
	return kind;
}

void Unit::setMediator(std::shared_ptr<Mediator> mediator)
{
	this->mediator = mediator;
}

std::shared_ptr<Mediator> Unit::getMediator()
{
	return mediator;
}

std::shared_ptr<Weapon> Unit::getWeapon()
{
	return weapon;
}

int Unit::getOwnDamage()
{
	return ownDamage;
}

int Unit::getLandDamage()
{
	return landDamage;
}

int Unit::getHP()
{
	return hp;
}

std::shared_ptr<Armor> Unit::getArmor()
{
	return armor;
}

int Unit::getOwnArmor()
{
	return ownArmor;
}

int Unit::getLandDefence()
{
	return landDamage;
}

std::shared_ptr<UnitSnapshot> Unit::getSnapshot()
{
    return std::shared_ptr<UnitSnapshot>(new UnitSnapshot(type, hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, lastStep));
}

Unit & Unit::operator+=(NeutralObject & obj)
{
	obj.affectOnUnit(shared_from_this());
	return *this;
}

//Unit & operator+=(std::shared_ptr<Unit> unit, NeutralObject& obj)
//{
//	obj.affectOnUnit(unit);
//	return *unit;
//}

std::ostream & operator<<(std::ostream & out, std::shared_ptr<Unit> unit)
{
	out << "Unit state: hp = " << unit->getHP() << " damage = " << unit->getLandDamage() + unit->getOwnDamage() + unit->getWeapon()->getDamage() << " armor = " << unit->getArmor()->getDefend() + unit->getLandDefence() + unit->getOwnArmor() << "\n";
	return out;
}


std::string Unit::getPath() {
    return "";
}


bool Unit::isDead() {
    return hp <= 0;
}


void Unit::kill() {
    hp = 0;
}

void Unit::setLastStep(size_t step) {
    this->lastStep = step;
}


size_t Unit::getLastStep() {
    return lastStep;
}
