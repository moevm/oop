#include "Base.h"

bool Base::addUnit(Unit *unit, Point position) {
    if (units.size() < limit){

        units.push_back(unit);
        for (auto bo: baseObservers){
            bo->onBaseNewUnit(unit, position);
        }
        Log::log << "[#Base] Unit added";
        return true;

    } else{

        Log::log << "[#Base] Can't add unit" << Log::logend;
        return false;

    }
}

void Base::onUnitAttack(Unit *unit, Unit *other) {
    Log::log << "[#Base]" << *unit << " attack\n";
}

void Base::onUnitMove(Unit *unit, Point p) {

    Log::log << "[#Base] " << *unit << " moving" << Log::logend;

}

void Base::onUnitDestroy(Unit *unit) {

    auto pos = std::find(units.begin(), units.end(), unit);
    if (pos != units.end()) {
        units.erase(pos);
        Log::log << "[#Base] " << *unit << " killed" << Log::logend;
    } else{
        Log::log << "Called observer of base for unit don't belong to it" << Log::logend;
    }

}

void Base::onUnitDamaged(Unit *unit) {

    Log::log << "[#Base] " << *unit << " damaged" << Log::logend;

}

void Base::onUnitHeal(Unit *unit) {

    Log::log << "[#Base] " << *unit << " healed" << Log::logend;

}

void Base::print(std::ostream &stream) const {

    stream << "B";

}

void Base::addObserver(BaseObserver *baseObserver) {

    baseObservers.push_back(baseObserver);
    Log::log << "[#Base] added observer" << Log::logend;

}