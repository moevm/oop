#include "BitingZomby.h"



BitingZomby::BitingZomby()
{
	weapon = std::shared_ptr<Weapon>(new BitingHead());
	type = UnitType::BITING_ZOMBY;
    attackBehavior = std::shared_ptr<AttackBehavior>(new BiteAttack());
}

BitingZomby::BitingZomby(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep)
:CommonZomby(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep){
	weapon = std::shared_ptr<Weapon>(new BitingHead());
	type = UnitType::BITING_ZOMBY;
    attackBehavior = std::shared_ptr<AttackBehavior>(new BiteAttack());
}

BitingZomby::BitingZomby(int x, int y, int level):CommonZomby(x, y, level) {
	weapon = std::shared_ptr<Weapon>(new BitingHead());
	type = UnitType::BITING_ZOMBY;
    attackBehavior = std::shared_ptr<AttackBehavior>(new BiteAttack());
}

BitingZomby::BitingZomby(const BitingZomby & other):CommonZomby(other) {

}

BitingZomby::BitingZomby(BitingZomby && other):CommonZomby(other)
{
}

BitingZomby& BitingZomby::operator=(const BitingZomby & other)
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

	return *this;
}

BitingZomby & BitingZomby::operator=(BitingZomby && other)
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

	return *this;
}


BitingZomby::~BitingZomby() {
}

char BitingZomby::getChar()
{
	return 'Z';
}


std::string BitingZomby::getPath() {
    return "bitingZomby.png";
}
