#ifndef OOP_LAB1_UNIT_H
#define OOP_LAB1_UNIT_H

#include "../Armor/Armor.h"
#include "../Weapon/Weapon.h"
#include "../Point.h"
#include "../GameObject.h"
#include "../Observers/UnitObserver.h"
#include "../Proxy/TextureProxy.h"
#include "../NeutralObject/NeutralObject.h"
#include "../FlyWeight/WeaponFlyWeight.h"
#include "../FlyWeight/ArmorFlyWeight.h"

#include <vector>
#include <ostream>

enum class UnitType {
  VIKING,
  WIZARD,
  ARCHER
};

class UnitObserver;

class Unit : public GameObject {
 protected:
  std::vector<UnitObserver *> unitObservers;
  UnitType unitType;

  Armor &unitArmor;
  Weapon &unitWeapon;
  int unitHealth;

  void print(std::ostream &stream) const override;

 public:

  Unit(const Unit &other);
  Unit(UnitType unitType, Armor &armor, Weapon &weapon, int health);

  Weapon &getUnitWeapon() {
    return unitWeapon;
  }
  Armor &getUnitArmor() {
    return unitArmor;
  }
  UnitType getUnitType() {
    return unitType;
  }
  int getUnitHealth();

  void move(Point position);
  void attack(Unit &other);
  void damage(int damage);
  void heal(int hp);

  void addObserver(UnitObserver *observer);

  Unit &operator=(const Unit &other);
  Unit &operator<<(NeutralObject *neutralObject);

  ~Unit();
};

#endif //OOP_LAB1_UNIT_H