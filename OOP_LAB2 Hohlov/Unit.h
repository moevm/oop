
#ifndef OOP_LAB1_UNIT_H
#define OOP_LAB1_UNIT_H

#include "Armor.h"
#include "Weapon.h"
#include "Point.h"
#include <vector>
#include <ostream>
#include "Armor.h"
#include "Weapon.h"
#include "Point.h"
#include "GameObject.h"
#include "UnitObserver.h"
#include "LandscapeProxy.h"
#include "NeutralObject.h"

enum class UnitType{

    VIKINGS,
    WIZARD,
    ARCHER

};

class Unit: public GameObject {

protected:

    std::vector<UnitObserver*> observers;

    UnitType unitType;

    Armor &armor;
    Weapon &weapon;
    int health;

    void print(std::ostream &stream) const override;

public:

    Unit(const Unit &other);
    Unit(UnitType unitType, Armor &armor, Weapon &weapon, int health);

    Weapon &getWeapon(){ return weapon; }
    Armor &getArmor(){ return armor; }

    void move(Point position);
    void attack(Unit &other);
    void damage(int damage);
    void heal(int hp);

    void addObserver(UnitObserver *observer);
    Unit& operator=(const Unit &other);
    Unit& operator<<(NeutralObject *neutralObject);

    UnitType getUnitType(){ return unitType; }

    int getHealth();

    ~Unit();

};


#endif //OOP_LAB1_UNIT_H
