#include "armorobject.hpp"

ArmorObject::ArmorObject(const ArmorObject& object)
{
    if (object.strategyPattern) {
        this->strategyPattern = object.strategyPattern->clone();
    }
}


ArmorObject& ArmorObject::operator=(const ArmorObject& object)
{
    if (this == &object) {
        return *this;
    }

    if (object.strategyPattern) {
        this->strategyPattern = object.strategyPattern->clone();
    }

    return *this;
}


std::shared_ptr<NeutralObject> ArmorObject::clone() const
{
    std::unique_ptr<NeutralObject> object(new ArmorObject(*this));
    return object;
}


void ArmorObject::selectLogic(std::shared_ptr<Unit> unit)
{
    if (typeid (unit.get()) == typeid (SwordMan)) {
        strategyPattern = std::unique_ptr<StrategyPattern>(new SwordManArmorUpdateLogic);
    }
    else if (typeid (unit.get()) == typeid (SpearMan)) {
        strategyPattern = std::unique_ptr<StrategyPattern>(new SpearManArmorUpdateLogic);
    }
    else if (typeid (unit.get()) == typeid (Archer)) {
        strategyPattern = std::unique_ptr<StrategyPattern>(new ArcherArmorUpdateLogic);
    }
    else if (typeid (unit.get()) == typeid (Dragon)) {
        strategyPattern = std::unique_ptr<StrategyPattern>(new DragonArmorUpdateLogic);
    }
    else {
        strategyPattern = std::unique_ptr<StrategyPattern>(new NoLogic);
    }
}

char ArmorObject::draw() const
{
    return 'a';
}
