#include "Base.h"
bool Base::canAddUnit(Unit *unit, Point position) {
  if (currentUnits.size() < maxObjectsCount) {
    currentUnits.push_back(unit);
    for (auto baseObserver : baseObservers) {
      baseObserver->onBaseNewUnitCreated(unit, position);
    }
    return true;
  } else {
    return false;
  }
}

void Base::onUnitAttack(Unit *unit, Unit *other) {
  std::cout << "Base: Unit " << unit << " attacking" << std::endl;
}

void Base::onUnitMoved(Unit *unit, Point p) {
  std::cout << "Base: Unit " << unit << " moving" << std::endl;
}

void Base::onUnitDestroyed(Unit *unit) {
  auto position = std::find(currentUnits.begin(), currentUnits.end(), unit);
  if (position != currentUnits.end()) {
    currentUnits.erase(position); // Удаление уничтоженного юнита из принадлежащих к этой базе
    std::cout << "Base: Unit " << unit << " was destroyed" << std::endl;
  } else {
    std::cout << "Called Base observer for unit doesn't belong to it" << std::endl;
  }
}

void Base::onUnitDamaged(Unit *unit) {
  std::cout << "Base: Unit " << unit << " damaged" << std::endl;
}

void Base::onUnitHealed(Unit *unit) {
  std::cout << "Base: Unit " << unit << " healed" << std::endl;
}

void Base::print(std::ostream &stream) const {
  stream << "BASE";
}

void Base::addBaseObserver(BaseObserver *baseObserver) {
  baseObservers.push_back(baseObserver);
}