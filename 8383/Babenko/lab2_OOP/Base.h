#ifndef INC_1_LAB_BASE_H
#define INC_1_LAB_BASE_H

#include "Armor/Armor.h"
#include "GameObject.h"
#include "Observers/UnitObserver.h"
#include "Observers/BaseObserver.h"

#include <vector>
#include <iostream>
#include <algorithm>

class Base : public GameObject, public UnitObserver {

 private:
  std::vector<BaseObserver *> baseObservers;
  std::vector<Unit *> currentUnits;
  int baseHealth;
  const int maxObjectsCount = 6;
  Armor baseArmor;

 protected:
  void print(std::ostream &stream) const override;

 public:
  Base(int health, Armor &armorType) : GameObject(ObjectType::BASE)
  {
    baseArmor = armorType;
    baseHealth = health;
  }
  bool canAddUnit(Unit *unit, Point position);
  void addBaseObserver(BaseObserver *baseObserver);

  template<typename T>
  T *createUnit(Point position) {
    if (currentUnits.size() < maxObjectsCount) {
      T *unit = new T();
      currentUnits.push_back(unit);
      unit->addObserver(this);
      for (auto baseObserver : baseObservers)
        baseObserver->onBaseNewUnitCreated(unit, position);
      return unit;
    } else {
      std::cout << "Base: Cannot create anymore units. Limit is exceeded." << std::endl;
    }
  }

  void onUnitAttack(Unit *unit, Unit *other) override;
  void onUnitMoved(Unit *unit, Point p) override;
  void onUnitDestroyed(Unit *unit) override;
  void onUnitDamaged(Unit *unit) override;
  void onUnitHealed(Unit *unit) override;
};

#endif //INC_1_LAB_BASE_H
