#include "HumanOnBike.h"



HumanOnBike::HumanOnBike()
{
	attackBehavior = std::shared_ptr<AttackBehavior>(new BikeAttack());
	moveBehavior = std::shared_ptr<MoveBehavior>(new BikeMove());
	weapon = std::shared_ptr<Weapon>(new Bat());
	type = UnitType::HUMAN_ON_BIKE;
}

HumanOnBike::HumanOnBike(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep)
:HumanOnMachine(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep){
	attackBehavior = std::shared_ptr<AttackBehavior>(new BikeAttack());
	moveBehavior = std::shared_ptr<MoveBehavior>(new BikeMove());
	weapon = std::shared_ptr<Weapon>(new Bat());
	type = UnitType::HUMAN_ON_BIKE;
}

HumanOnBike::HumanOnBike(int x, int y, int level):HumanOnMachine(x, y, level)
{
	attackBehavior = std::shared_ptr<AttackBehavior>(new BikeAttack());
	moveBehavior = std::shared_ptr<MoveBehavior>(new BikeMove());
	weapon = std::shared_ptr<Weapon>(new Bat());
	type = UnitType::HUMAN_ON_BIKE;
}

HumanOnBike::HumanOnBike(const HumanOnBike & other):HumanOnMachine(other)
{
}

HumanOnBike::HumanOnBike(HumanOnBike && other):HumanOnMachine(other)
{
}

HumanOnBike& HumanOnBike::operator=(const HumanOnBike & other)
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

HumanOnBike & HumanOnBike::operator=(HumanOnBike && other)
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


HumanOnBike::~HumanOnBike()
{
}

char HumanOnBike::getChar()
{
	return 'M';
}


std::string HumanOnBike::getPath() {
    return "humanOnBoke.png";
}
