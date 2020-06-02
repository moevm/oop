#ifndef INC_1_LAB_WEAPONFLYWEIGHT_H
#define INC_1_LAB_WEAPONFLYWEIGHT_H

#include <vector>
#include "../Weapon/Weapon.h"

class WeaponFlyWeight {
 private:
  static WeaponFlyWeight *self;
  std::vector<Weapon *> availableWeapons;

 public:
  template<typename T>
  static T *getFlyWeight() {
    if (!self)
      self = new WeaponFlyWeight();
    T needWeapon;
    for (auto *weapon: self->availableWeapons) {
      if (needWeapon == *weapon) {
        return static_cast<T *>(weapon);
      }
    }

    T *weaponPtr = new T();
    self->availableWeapons.push_back(weaponPtr);
    return weaponPtr;
  }
};

#endif //INC_1_LAB_WEAPONFLYWEIGHT_H
