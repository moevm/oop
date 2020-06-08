#ifndef OOP_UNIT_H
#define OOP_UNIT_H
#include "Unit.h"

#include <iostream>
#include <vector>
#include "../neutralObjects/NeutralObject.h"

#include "attributes/Health.h"
#include "attributes/Attack.h"
#include "attributes/Defense.h"

#include "../Subject.h"
#include "../Observer.h"


enum UnitName {HALBERDIER, SKELETON, ARCHER, LICH, GRIFFIN, BONE_DRAGON};

// component
class Unit : public Subject{
public:
    void changeAttributes(int attack, int defense, int health);
    void setAttributes(int attack, int defense, int health);
    void printAttributeValues();
    void setCoordinates(int x, int y) final;
    int getHealthValue() {return health->getValue();};
    int getAttackValue() {return attack->getValue();};
    int getDefenseValue() {return defense->getValue();};
    Coordinates * getCoordinates() final {return coordinates;};
    UnitName getUnitName() {return unitName;};
    virtual ~Unit() = default;
    virtual Unit& operator+=(NeutralObject &object) = 0;
    void notifyObservers(std::string *newAction) final;
    void addObservers(Observer *observer) final;
protected:
    explicit Unit() {};
    UnitName unitName;
private:
    std::vector <Observer*> observers;
    Coordinates *coordinates;
    Attack *attack;
    Defense *defense;
    Health *health;
};
#endif //OOP_UNIT_H
