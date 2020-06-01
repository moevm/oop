#pragma once
#include "Flyweight.h"
#include "Field.h"
#include "ArmyFactory.h"
#include "observer_interfaces.h"

class Base : public FieldObject, IBase
{
protected:
	std::string name;
	int healPoints = 0;

	unsigned maxCreateUnits;

	ArmyFactory* warriorFactory;
	ArmyFactory* shooterFactory;
	ArmyFactory* bufferFactory;

	FlyweightFactory* flyweightFactory;

	PlayingField* field;
	//sf::Sprite sprite
	std::vector<Unit*> units;

	bool team;

public:
	Base(int maxCreateUnits = 1, PlayingField* field_ = nullptr, int X = 0, int Y = 0, bool team = true);
	~Base() {
		delete warriorFactory;
		delete shooterFactory;
		delete bufferFactory;
		delete flyweightFactory;
	}

	//virtual void render(sf::RenderWindow& window) const;
	void setMaxCreateUnits(int newMax);
	virtual std::string getName();
	virtual std::string getShortName();
	virtual std::string info();
	virtual std::string getAbstractClass() {
		return "Base";
	}
	virtual void unitInfluence(Unit* unit) {}
	bool isAlive() {
		return alive;
	}
	bool getTeam() {
		return team;
	}
	bool isMovable() {
		return canMove;
	}
	void setAlive(bool flag) {
		alive = flag;
	}
	FieldObject* copy()
	{
		return new Base(*this);
	}

	void getDamage(int damage) {
		healPoints -= damage;
		if (healPoints <= 0) {
			setAlive(false);
		}
	}

	bool createUnit(std::string UnitType, std::string color,unsigned row, unsigned column);


	Unit* createUnit_(std::string UnitType, std::string color, unsigned row, unsigned column);//for lab 2


	void onUnitDestroyed(Unit* destroyedUnit) {
		
		for (unsigned int i = 0; i < units.size();i++) {
			if (units[i] == destroyedUnit) {
				units.erase(units.begin()+i);
				field->deleteObject(destroyedUnit);
				std::cout << "Base: Unit deleted\n";
				return;
			}
		}
	}
};

