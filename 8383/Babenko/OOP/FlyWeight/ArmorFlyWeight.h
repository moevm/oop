#ifndef INC_1_LAB_ARMORFLYWEIGHT_H
#define INC_1_LAB_ARMORFLYWEIGHT_H

#include <vector>
#include "../Armor/Armor.h"

class ArmorFlyWeight {
 private:
  static ArmorFlyWeight *self;
  std::vector<Armor *> availableArmors;

 public:
  template<typename T>
  static T *getFlyWeight() {
    if (!self)
      self = new ArmorFlyWeight();

    T needArmor;
    for (auto *armor: self->availableArmors) {
      if (needArmor == *armor) {
        return static_cast<T *>(armor);
      }
    }

    T *armorPtr = new T();
    self->availableArmors.push_back(armorPtr);
    return armorPtr;
  }
};

#endif //INC_1_LAB_ARMORFLYWEIGHT_H
