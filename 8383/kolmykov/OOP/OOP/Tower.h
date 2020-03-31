#pragma once
#include "ObserverInterface.h"
#include <memory>
#include <iostream>
#include "TowerSnapshot.h"


class Mediator;
class UnitFactory;
class Unit;


class Tower: public  ObserverInterface {
private:
	int level;
	int hp;
	int damage;
	int size;
	int unitCount;
	std::shared_ptr<UnitFactory> factory;
	std::shared_ptr<Mediator> mediator;
public:
	Tower(int x, int y, std::shared_ptr<UnitFactory> factory);
	Tower(int level, int hp, int damage, int size, int unitCount, std::shared_ptr<UnitFactory> factory, std::shared_ptr<Mediator> mediator);
	Tower(const Tower& other);
	Tower(Tower&& other);
	~Tower();
	void update();
	void levelUp();
	void updateKill();
	bool canCreateUnit();
	std::shared_ptr<Unit> createUnit(int x, int y, int level);
	int getLevel();
	void damageTower(int damage);
	int getHP();
	int getDamage();
	void setMediator(std::shared_ptr<Mediator> mediator);
	void attack();
	int getX();
	int getY();
	int getSize();
	std::shared_ptr<TowerSnapshot> getSnapshot();
};

std::ostream& operator<<(std::ostream &out, std::shared_ptr<Tower> tower);