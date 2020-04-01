#pragma once
#include "AttackBehavior.h"
#include "MoveBehavior.h"
#include "Armor.h"
#include <memory>
#include "Weapon.h"
#include "UnitInterface.h"
#include "SubjectInterface.h"
#include "NeutralObject.h"
#include "Kind.h"
#include "Mediator.h"
#include <ostream>
#include "UnitType.h"
#include "UnitSnapshot.h"


class Unit : public UnitInterface, public SubjectInterface, public std::enable_shared_from_this<Unit> {
protected:
	Kind kind;
	UnitType type;
	int hp;
	int maxHP;
	int ownArmor;
	int ownDamage;
	bool visability;
	int level;
	int landDamage;
	int landDefence;
	std::shared_ptr<Weapon> weapon;
	std::shared_ptr<Armor> armor;
	std::shared_ptr<MoveBehavior> moveBehavior;
	std::shared_ptr<AttackBehavior> attackBehavior;
	std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers;
	int observerSize;
	int observerCount;
	int coordX;
	int coordY;
	std::shared_ptr<Mediator> mediator;
    size_t lastStep;
	
public:
    Unit(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	Unit();
	Unit(int x, int y, int lvl);
	Unit(const Unit& other);
	Unit(Unit&& other);
	Unit& operator=(const Unit& other);
	Unit& operator=(Unit&& other);
	virtual ~Unit();
	void performAttack();
	void performMove();
	void damageUnit(int damage);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	virtual char getChar();
	void levelUp();
	void registerObserever(std::shared_ptr<ObserverInterface> observer);
	void removeObserver(std::shared_ptr<ObserverInterface> observer);
	void notifyObservers();
	void notifyAboutKill();
	void setVisability(bool visability);
	bool getVisability();
	void setLandDamage(int damage);
	void setLandDefence(int defence);
	void addHP(int hp);
	void addArmor(int defence);
	Kind getKind();
	void setMediator(std::shared_ptr<Mediator> mediator);
	std::shared_ptr<Mediator> getMediator();
	std::shared_ptr<Weapon> getWeapon();
	int getOwnDamage();
	int getLandDamage();
	int getHP();
	std::shared_ptr<Armor> getArmor();
	int getOwnArmor();
	int getLandDefence();
	std::shared_ptr<UnitSnapshot> getSnapshot();
    virtual std::string getPath();
    bool isDead();
    void kill();
    size_t getLastStep();
    void setLastStep(size_t step);

	Unit& operator+= (NeutralObject& obj);
};

//Unit& operator+= (std::shared_ptr<Unit> unit, NeutralObject& obj);

std::ostream& operator << (std::ostream& out, std::shared_ptr<Unit> unit);
