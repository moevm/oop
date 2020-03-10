#pragma once

#include <cmath>
#include <utility>
#include <memory>

class Field;

class location {
public:
	location(int x, int y) {
		this->position.first = x;
		this->position.second = y;
	}

	explicit location(std::pair<int, int> pos) {
		this->position = pos;
	}

	location() = default;
	~location() = default;

	void setPosition(int x, int y) {
		this->position.first = x;
		this->position.second = y;
	}

	void setPosition(std::pair<int, int> pos) {
		this->position = pos;
	}

	std::pair<int, int> getPosition() const {
		return position;
	}

private:
	std::pair<int, int> position;


};


class Health
{
public:
	Health() {
		health = 0;
	}
	~Health() = default;

	explicit Health(int h) {
		this->health = h;
	}

	int getHealth() {
		return health;

	}

	void setHealth(int h) {
		this->health = h;
	}

	void actDamaged(int dmg) {

		this->health -= dmg;
	}

	void actHealed(int heal) {
		this->health += heal;
	}

private:
	int health;

};



class Damage
{
public:
	Damage() {
		damage = 0;
		range = 0;
	}
	~Damage() = default;

	Damage(int d, int r) {
		this->damage = d;
		this->range = r;
	}

	int getDamage() const {
		return damage;

	}

	void setDamage(int d) {
		damage = d;
	}

	int getRange() const {
		return range;

	}

	void setRange(int r) {
		range = r;
	}

	void actDecreaseDmg(int debuff) {

		damage -= debuff;
	}

	void actIncreaseDmg(int buff) {
		damage += buff;
	}

private:
	int damage;
	int range;

};


class Armor
{
public:

	Armor() {
		armor = 0;
	}
	~Armor() = default;

	explicit Armor(int a) {
		this->armor = a;
	}

	int getArmor() const {
		return armor;

	}

	void setArmor(int a) {
		armor = a;
	}

	void actDecreaseArmor(int debuff) {

		armor -= debuff;
	}

	void actIncreaseArmor(int buff) {
		armor += buff;
	}

private:
	int armor;

};


class Unit :public Armor, public Health, public Damage, public location
{
public:
	Unit() = default;

	virtual Unit* clone() = 0;

	virtual ~Unit() = 0;

	void move(Field *f, int dX, int dY);

	void attack(Field *f, Unit* target);
};



class Ballista :public Unit
{
public:
	Ballista() = default;

	explicit Ballista(int health, int dmg, int range, int armor);

	~Ballista() override = 0;

};



class Mortar : public Ballista {

public:
	Mortar() : Ballista(500, 50, 10, 15)
	{};

	Unit* clone() final {
		auto tmp = new Mortar;

		tmp->setHealth(this->getHealth());

		tmp->setDamage(this->getDamage());

		tmp->setRange(this->getRange());

		tmp->setArmor(this->getArmor());

		return (Unit*)tmp;

	}

	~Mortar() final = default;
};


class Catapult : public Ballista {

public:
	Catapult() : Ballista(300, 30, 10, 8)
	{};

	Unit* clone() final {
		auto tmp = new Catapult;

		tmp->setHealth(this->getHealth());

		tmp->setDamage(this->getDamage());

		tmp->setRange(this->getRange());

		tmp->setArmor(this->getArmor());

		return (Unit*)tmp;

	}

	~Catapult() final = default;
};


class Berserker : public Unit {

public:

	Berserker() = default;

	explicit Berserker(int health, int dmg, int range, int armor);

	~Berserker() override = 0;

};



class Spearman : public Berserker {

public:
	Spearman() : Berserker(1400, 75, 2, 35)
	{};

	Unit* clone() final {
		auto tmp = new Spearman;

		tmp->setHealth(this->getHealth());

		tmp->setDamage(this->getDamage());

		tmp->setRange(this->getRange());

		tmp->setArmor(this->getArmor());

		return (Unit*)tmp;

	}

	~Spearman() final = default;
};


class Rogue : public Berserker {

public:
	Rogue() : Berserker(900, 40, 5, 25)
	{};

	Unit* clone() final {
		auto tmp = new Rogue;

		tmp->setHealth(this->getHealth());

		tmp->setDamage(this->getDamage());

		tmp->setRange(this->getRange());

		tmp->setArmor(this->getArmor());

		return (Unit*)tmp;

	}

	~Rogue() final = default;
};



class Horseman : public Unit {

public:

	Horseman() = default;

	explicit Horseman(int health, int dmg, int range, int armor);

	~Horseman() override = 0;
};



class HorsemenLeader : public Horseman {

public:
	HorsemenLeader() : Horseman(800, 60, 8, 20)
	{};

	Unit* clone() final {
		auto tmp = new HorsemenLeader;

		tmp->setHealth(this->getHealth());

		tmp->setDamage(this->getDamage());

		tmp->setRange(this->getRange());

		tmp->setArmor(this->getArmor());

		return (Unit*)tmp;

	}

	~HorsemenLeader() final = default;
};


class RegularHorseman : public Horseman {

public:
	RegularHorseman() : Horseman(600, 55, 8, 20)
	{};

	Unit* clone() final {
		auto tmp = new RegularHorseman;

		tmp->setHealth(this->getHealth());

		tmp->setDamage(this->getDamage());

		tmp->setRange(this->getRange());

		tmp->setArmor(this->getArmor());

		return (Unit*)tmp;

	}

	~RegularHorseman() final = default;
};





















